#include "../include/driver.h"

#include <stdlib.h>
#include <stdio.h>
#include <poly.h> 


void msf_init_special(int speed, int num_frames, int num_channels, int num_phrases, int phrase_length, int num_instruments, msf_driver *driver)
{
	driver->speed = speed;
	driver->num_frames = num_frames;
	driver->num_channels = num_channels;
	driver->num_phrases = num_phrases;
	driver->phrase_length = phrase_length;
	driver->num_instruments = num_instruments;

// Reset state variables
	driver->frame_cnt = 0;
	driver->phrase_cnt = 0;
	driver->phrase_adv = 0;

	driver->frames = malloc(sizeof(msf_frame *) * num_frames);
	driver->phrases = malloc(sizeof(msf_phrase *) * num_phrases);
	driver->instruments = malloc(sizeof(msf_instrument *) * num_instruments);

	// Actually build the structs the above pointer arrays point to
	for (int i = 0; i < num_frames; i++)
	{
		driver->frames[i] = msf_create_frame(num_channels);
	}

	for (int i = 0; i < num_phrases; i++)
	{
		driver->phrases[i] = msf_create_phrase(phrase_length);
	}

	for (int i = 0; i < num_instruments; i++)
	{
		driver->instruments[i] = msf_create_instrument();
		driver->instruments[i]->amp_macro->value = 255; // Default to full blast
	}

	// Point these to the LL macros (one per channel);
	driver->arp = malloc(num_channels * sizeof(msf_ll *));
	driver->amp = malloc(num_channels * sizeof(msf_ll *));
	driver->pitch = malloc(num_channels * sizeof(msf_ll *));
	driver->duty = malloc(num_channels * sizeof(msf_ll *));
	for (int i = 0; i < num_channels; i++) // Null them out to avoid confusion
	{
		driver->arp[i] = NULL;
		driver->amp[i] = NULL;
		driver->pitch[i] = NULL;
		driver->duty[i] = NULL;
	}
	driver->init = 1;
	driver->loopback = 0;
	driver->track_length = 1;

	driver->amp_l = malloc(sizeof(float *) * num_channels);
	driver->amp_r= malloc(sizeof(float *) * num_channels);
	driver->freq = malloc(sizeof(float *) * num_channels);
	driver->note = malloc(sizeof(int *) * num_channels);

	// Initialize libPOLY6 with the parametres from above
	poly_init(16,2,44100,num_channels,NULL);
	for (int i = 0; i < num_channels; i++)
	{
		poly_init_generator(i,square,0.0,440 + (8*i));
	}
	poly_start();
}

// Simple shortcut init with some usable (but maybe too large) defaults
void msf_init(msf_driver *driver)
{
	msf_init_special(
	MSF_DEFAULT_SPEED,
	MSF_NUM_FRAMES,
	MSF_NUM_CHANNELS,
	MSF_NUM_PHRASES,
	MSF_PHRASE_LENGTH,
	MSF_NUM_INSTRUMENTS,
	driver);
}

// Steps through channel [i]'s linked lists
void msf_drv_inc_ll(msf_driver *driver, int i)
{
	// Advance the macro LLs
	if (driver->arp[i] != NULL && driver->arp[i]->next != NULL)
	{
		driver->arp[i] = driver->arp[i]->next;	
	}
	if (driver->amp[i] != NULL && driver->amp[i]->next != NULL)
	{
		driver->amp[i] = driver->amp[i]->next;
	}
	if (driver->pitch[i] != NULL && driver->pitch[i]->next != NULL)
	{
		driver->pitch[i] = driver->pitch[i]->next;	
	}
	if (driver->duty[i] != NULL && driver->duty[i]->next != NULL)
	{
		driver->duty[i] = driver->duty[i]->next;
	}
}

// Increments the position counter
// Returns 1 if it is a new step
int msf_drv_proc(msf_driver *driver)
{
	int new_step = 0;

	// Step through the song

	if (driver->phrase_adv == 0 && driver->phrase_cnt == 0)
	{
		new_step = 1;
	}
	if (driver->phrase_adv == driver->speed) // Time to go to next step
	{
		driver->phrase_adv = 0;
		driver->phrase_cnt++;
		new_step = 1;
	}
	driver->frames[0]->tune[3] = 16;
	if (driver->phrase_cnt == driver->phrase_length) // End of phrase
	{	
		printf("Moving to frame %d, channel 0 has phrase %d.\n",driver->frame_cnt,driver->frames[driver->frame_cnt]->phrase[0]);
		driver->frame_cnt++;
		driver->phrase_cnt = 0;
		driver->phrase_adv = 0;
	}
	if (driver->frame_cnt == driver->track_length) // End of song
	{
		driver->phrase_cnt = 0;
		driver->phrase_adv = 0;
		driver->frame_cnt = driver->loopback;
	}
	return new_step;
}

void msf_step(msf_driver *driver)
{
	int new_step = msf_drv_proc(driver);
	
	// Loop through each channel
	for (int i = 0; i < driver->num_channels; i++)
	{
		// Pull the phrase number for channel i from the current frame
		int phrase_num = driver->frames[driver->frame_cnt]->phrase[i];
		
		// The phrase itself
		msf_phrase *phrase = driver->phrases[phrase_num];

		// Instrument for the current phrase at the current time
		msf_instrument *instrument = driver->instruments[phrase->inst[driver->phrase_cnt]];
		
		if (phrase->note[driver->phrase_cnt] == -1) // Note kill
		{
			poly_set_amplitude(i,0);
			driver->amp_l[i] = 0;
			driver->amp_r[i] = 0;
			driver->note[i] = -1;
		}
		if (new_step && phrase->note[driver->phrase_cnt] != 0 && phrase->inst[driver->phrase_cnt] != -1) // If there is a note to set
		{
			// Set the note
			// Reset our macro traversal
			driver->arp[i] = instrument->arp_macro;
			driver->amp[i] = instrument->amp_macro;
			driver->pitch[i] = instrument->pitch_macro;
			driver->duty[i] = instrument->duty_macro;
			driver->note[i] = phrase->note[driver->phrase_cnt];
			driver->amp_l[i] = instrument->left_amp;
			driver->amp_r[i] = instrument->right_amp;
			
			// Set note with transposition
			driver->freq[i] = 0; // Zero out the frequency offset from the pitch macro
			driver->note[i] = driver->note[i];
			
			// Set L/R balance
			poly_set_R_amp(i,driver->amp_r[i]);
			poly_set_L_amp(i,driver->amp_l[i]);
			
			// Set up wave type
			switch(instrument->type)
			{
			case WAVE_SQUARE:
				poly_set_wavetype(i,square);
				break;
			case WAVE_SINE:
				poly_set_wavetype(i,sine);
				break;
			case WAVE_SAW:
				poly_set_wavetype(i,saw);
				break;
			case WAVE_TRIANGLE:
				poly_set_wavetype(i,triangle);
				break;
			case WAVE_NOISE:
				poly_set_wavetype(i,noise);
				break;
				// The rest will come once libpoly supports them properly
			}
		}
		else
		{
			msf_drv_inc_ll(driver, i);
		}
		
		//  ------------------------------------------------------------------------------
		// | Commit information loaded from instrument data / runtime data to synthesizer |
		//  ------------------------------------------------------------------------------
		
		// Apply frequency offset from macro LL
		if (driver->pitch[i] != NULL)
		{
			driver->freq[i] += ((float)driver->pitch[i]->value / MSF_TUNE_DIV);
		}
		
		int arp_off = 0;
		if (driver->arp[i] != NULL)
		{
			arp_off = driver->arp[i]->value;
		}
		
		// Set the channel frequency
		// Considering: frequency from (note + arp offset + transpose) + pitch bend sum
		poly_set_freq(i,msf_get_freq(driver->note[i] + arp_off + driver->frames[driver->frame_cnt]->transpose[i]) + driver->freq[i]);
		
		// Set duty
		if (driver->duty[i] != NULL)
		{
			poly_set_duty(i,(driver->duty[i]->value/255.0));
		}
		
		// Commit master amplitude from macro
		if (driver->note[i] != -1)
		{
			if (driver->amp[i] != NULL)
			{
				poly_set_amplitude(i,driver->amp[i]->value/255.0);
			}
			else
			{
				poly_set_amplitude(i,0);
			}
		}
	}
	driver->phrase_adv++;
}

void msf_spill(msf_driver *driver)
{
	printf("%d\t%d\t%d\n",driver->frame_cnt,driver->phrase_cnt,driver->phrase_adv);
}

void msf_shutdown(msf_driver *driver)
{
	poly_stop();
	poly_shutdown();
	if (driver->init == 1)
	{
		for (int i = 0; i < driver->num_frames; i++)
		{
			msf_destroy_frame(driver->frames[i]);
		}
		for (int i = 0; i < driver->num_phrases; i++)
		{
			msf_destroy_phrase(driver->phrases[i]);
		}
		for (int i = 0; i < driver->num_instruments; i++)
		{
			msf_destroy_instrument(driver->instruments[i]);
		}
		
		free(driver->frames);
		free(driver->phrases);
		free(driver->instruments);
		free(driver->arp);
		free(driver->amp);
		free(driver->pitch);
		free(driver->note);
		free(driver->amp_l);
		free(driver->amp_r);
		free(driver->freq);
		free(driver->duty);
	}
}
