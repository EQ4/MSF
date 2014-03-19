#include "../include/driver.h"


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
		//printf("Created instrument #%d at 0x%d.\n",i,(unsigned int)driver->instruments[i]);
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

void msf_step(msf_driver *driver)
{
	int new_step = 0;

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
		driver->frame_cnt++;
		driver->phrase_cnt = 0;
		driver->phrase_adv = 0;
		printf("Moving to frame %d, channel 0 has phrase %d.\n",driver->frame_cnt,driver->frames[driver->frame_cnt]->phrase[0]);
	}
	if (driver->frame_cnt == driver->track_length) // End of song
	{
		driver->phrase_cnt = 0;
		driver->phrase_adv = 0;
		driver->frame_cnt = driver->loopback;
	}
	
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
		//	printf("NOTE ON %d! -Value %d inst %d.\n",i,phrase->note[driver->phrase_cnt],phrase->inst[driver->phrase_cnt]);
			// Set the note
			// Reset our macro traversal
			driver->arp[i] = instrument->arp_macro;
			//printf("New arp macro: 0x%d\n",driver->arp[i]);
			driver->amp[i] = instrument->amp_macro;
			driver->pitch[i] = instrument->pitch_macro;
			driver->duty[i] = instrument->duty_macro;
			driver->note[i] = phrase->note[driver->phrase_cnt];
			driver->amp_l[i] = instrument->left_amp;
			driver->amp_r[i] = instrument->right_amp;
			

			poly_set_R_amp(i,driver->amp_r[i]);
			poly_set_L_amp(i,driver->amp_l[i]);
			
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
			// Advance the macro LLs
			if (driver->arp[i] != NULL && driver->arp[i]->next != NULL)
			{
			//	printf("Advancing arp LL\n");
				driver->arp[i] = driver->arp[i]->next;	
			}
			if (driver->amp[i] != NULL && driver->amp[i]->next != NULL)
			{
			//	printf("Advancing amp LL\n");
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
		if (driver->duty[i] != NULL)
		{
			poly_set_duty(i,(driver->duty[i]->value/255.0));
		}
		int arp_off = driver->frames[driver->frame_cnt]->transpose[i];
		if (driver->arp[i] != NULL)
		{
			//printf("Setting arp_off to %d.\n",driver->arp[i]->value);
			arp_off += driver->arp[i]->value;
		}
		float pitch_off = driver->frames[driver->frame_cnt]->tune[i] / MSF_TUNE_DIV;
		if (driver->pitch[i] != NULL)
		{
			pitch_off += driver->pitch[i]->value;
		}
		driver->freq[i] = msf_get_freq(driver->note[i] + arp_off) + pitch_off;
		
		if (i == 0)
		{
			// printf("Frequency is %f.\n",driver->freq[i]);
		}
		poly_set_freq(i,driver->freq[i]);
		if (driver->note[i] != -1 && driver->amp[i] != NULL)
		{
			poly_set_amplitude(i,driver->amp[i]->value/255.0);
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
			//printf("----%d: Destroying frame 0x%d\n",i,(unsigned int)driver->frames[i]);
			msf_destroy_frame(driver->frames[i]);
		}
		for (int i = 0; i < driver->num_phrases; i++)
		{
			//printf("----%d: Destroying phrase 0x%d\n",i,(unsigned int)driver->phrases[i]);
			msf_destroy_phrase(driver->phrases[i]);
		}
		for (int i = 0; i < driver->num_instruments; i++)
		{
			printf("----%d: Destroying instrument 0x%d\n",i,(unsigned int)driver->instruments[i]);
			msf_destroy_instrument(driver->instruments[i]);
		}
		
		//printf("----Freeing frames\n");
		free(driver->frames);
		//printf("----Freeing phrases\n");
		free(driver->phrases);
		//printf("----Freeing instruments\n");
		free(driver->instruments);
		//printf("----Freeing arp\n");
		free(driver->arp);
		//printf("----Freeing amp\n");
		free(driver->amp);
		//printf("----Freeing pitch\n");
		free(driver->pitch);
		//printf("----Freeing note\n");
		free(driver->note);
		//printf("----Freeing amp_l\n");
		free(driver->amp_l);
		//printf("----Freeing amp_r\n");
		free(driver->amp_r);
		//printf("----Freeing freq\n");
		free(driver->freq);
		free(driver->duty);
	}
}
