#include "driver.h"
#include "effects.h"
#include "instrument.h"
#include "txtcolor.h"

#include <stdlib.h>
#include <stdio.h>
#include <poly.h> 
#include <string.h>


msf_driver *msf_init_special(int speed, int num_frames, int num_channels, int num_phrases, int phrase_length, int num_instruments)
{
	msf_driver *driver = NULL;
	driver = (msf_driver*)malloc(sizeof(*driver));
	if (driver == NULL)
	{
		printf("Malloc was no good! %u was too much.\n",(unsigned int)sizeof(msf_driver));
		return NULL;
	}
	else
	{
		printf("Using new driver at 0x%u.\n",(unsigned int)driver);
	}
	driver->speed = speed;
	driver->num_frames = num_frames;
	driver->track_length = num_frames;
	printf("Track length: %i\n",num_frames);
	driver->num_channels = num_channels;
	driver->num_phrases = num_phrases;
	driver->phrase_length = phrase_length;
	driver->num_instruments = num_instruments;
	driver->name = NULL;
	driver->author = NULL;

// Reset state variables
	driver->frame_cnt = 0;
	driver->phrase_cnt = 0;
	driver->phrase_adv = 0;

	driver->hop_queue = -1;
	driver->jump_queue = -1;
	driver->frames = NULL;
	driver->phrases = NULL;
	driver->instruments = NULL;
	driver->frames = malloc(sizeof(msf_frame *) * num_frames);
	driver->phrases = malloc(sizeof(msf_phrase *) * num_phrases);
	driver->instruments = malloc(sizeof(msf_instrument *) * num_instruments);


	if (!driver->frames)
	{
		printf("Failed to malloc for frames.\n");
		free(driver);
		return NULL;
	}
	if (!driver->phrases)
	{
		printf("Failed to malloc for phrases.\n");
		free(driver);
		return NULL;
	}
	if (!driver->instruments)
	{
		printf("Failed to malloc for instruments.\n");
		free(driver);
		return NULL;
	}
	
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
	driver->note_delay = malloc(sizeof(int *) * num_channels);
	driver->note_cut = malloc(sizeof(int *) * num_channels);
	driver->init = 1;
	driver->loopback = 0;


	driver->amp_l = malloc(sizeof(float *) * num_channels);
	driver->amp_r= malloc(sizeof(float *) * num_channels);
	driver->freq = malloc(sizeof(float *) * num_channels);
	driver->note = malloc(sizeof(int *) * num_channels);
	for (int i = 0; i < num_channels; i++) // Null them out to avoid confusion
	{
		driver->arp[i] = NULL;
		driver->amp[i] = NULL;
		driver->pitch[i] = NULL;
		driver->duty[i] = NULL;
		driver->note_delay[i] = 0;
		driver->note_cut[i] = 0;
	}

			// Initialize libPOLY6 with the parametres from above
	printf("Initializing libPOLY\n");
	poly_init(16,2,44100,num_channels,NULL);
	printf("--Creating generators\n");
	for (int i = 0; i < num_channels; i++)
	{
		poly_init_generator(i,poly_square,0.0,440 + (8*i));
	}

	// Temporary grindy _-_-____---- square wave for sample test
	poly_sample *samp = (poly_sample *)malloc(sizeof(poly_sample));;
	samp->len = 32;
	samp->div = 1;
	samp->data = (float *)malloc(sizeof(float) * samp->len);
	for (int j = 0; j < samp->len; j++)
	{
		samp->data[j] = (j > samp->len / 2) ? 1.0 : -1.0;

	}
	samp->data[2] = 1.0;
	samp->data[4] = 1.0;
	printf("Created a test sample struct at %X, length %d\n",(unsigned int)samp,samp->len);
	for (int j = 0; j < num_channels; j++)
	{
		poly_set_sample(j,samp);
	}

	printf("--poly_start()\n");
	poly_start();
	printf("Giving back 0x%u.\n",(unsigned int)driver);
	return driver;
}
// Simple shortcut init with some usable (but maybe too large) defaults
msf_driver *msf_init()
{
	return msf_init_special(
	MSF_DEFAULT_SPEED,
	MSF_NUM_FRAMES,
	MSF_NUM_CHANNELS,
	MSF_NUM_PHRASES,
	MSF_PHRASE_LENGTH,
	MSF_NUM_INSTRUMENTS);
}

// Steps through channel [i]'s linked lists
void msf_drv_inc_ll(msf_driver *driver, int i)
{
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
	if (driver->phrase_adv >= driver->speed) // Time to go to next step
	{
		driver->phrase_adv = 0;
		driver->phrase_cnt++;
		new_step = 1;
		if (driver->hop_queue != -1)
		{
			driver->frame_cnt++;
			driver->phrase_cnt = driver->hop_queue;
			driver->phrase_adv = 0;
			printf("Hopping to frame %d, line %i.\n",driver->frame_cnt,driver->hop_queue);
			driver->hop_queue = -1;
		}
		if (driver->jump_queue != -1)
		{
			driver->phrase_cnt = 0;
			driver->frame_cnt = driver->jump_queue;
			driver->phrase_adv = 0;
			driver->jump_queue = -1;
			printf("Jumping to frame %d.\n",driver->frame_cnt);
		}
	}
	if (driver->phrase_cnt >= driver->phrase_length) // End of phrase
	{	
		driver->frame_cnt++;
		driver->phrase_cnt = 0;
		driver->phrase_adv = 0;
		textcolor(COL_BRIGHT,COL_BLUE,COL_BLACK);
		printf("[ Frame %d ]\n",driver->frame_cnt);
	}
	if (driver->frame_cnt >= driver->track_length) // End of song
	{
		driver->phrase_cnt = 0;
		driver->phrase_adv = 0;
		driver->frame_cnt = driver->loopback;
	}
	return new_step;
}

void msf_kill_channel(msf_driver *driver, int chan)
{
	if (chan < driver->num_channels)
	{
		poly_set_amplitude(chan,0);
		driver->amp_l[chan] = 0;
		driver->amp_r[chan] = 0;
		driver->note[chan] = -1;
	}
}

void msf_trigger_note(msf_driver *driver, int i, msf_instrument *instrument, int note)
{
	if (note > 0 && note < 0xFF)
	{
		//printf("Trigger on channel %i\n",i);
		driver->arp[i] = instrument->arp_macro;
		driver->amp[i] = instrument->amp_macro;
		driver->pitch[i] = instrument->pitch_macro;
		driver->duty[i] = instrument->duty_macro;
		driver->note[i] = note;
		driver->amp_l[i] = instrument->left_amp;
		driver->amp_r[i] = instrument->right_amp;
		
		// Set note with transposition
		driver->freq[i] = 0; // Zero out the frequency offset from the pitch macro
		
		// Set L/R balance
		poly_set_R_amp(i,driver->amp_r[i]);
		poly_set_L_amp(i,driver->amp_l[i]);


		// Set up wave type
		switch(instrument->type)
		{
		case WAVE_SQUARE:
			poly_set_wavetype(i,poly_square);
			break;
		case WAVE_SINE:
			poly_set_wavetype(i,poly_sine);
			break;
		case WAVE_SAW:
			poly_set_wavetype(i,poly_saw);
			break;
		case WAVE_TRIANGLE:
			poly_set_wavetype(i,poly_triangle);
			break;
		case WAVE_NOISE:
//			poly_set_wavetype(i,poly_noise);
			break;
		case WAVE_ONESAMPLE:
	//		poly_set_wavetype(i,poly_onesample);
			break;
		case WAVE_LOOPSAMPLE:
			poly_set_wavetype(i,poly_loopsample);
			break;
		}
	}
}

void msf_step(msf_driver *driver)
{
	int new_step = msf_drv_proc(driver);
	if (new_step)
	{
		msf_spill(driver);
	}	
	// Loop through each channel
	for (int i = 0; i < driver->num_channels; i++)
	{
		// Pull the phrase number for channel i from the current frame
		int phrase_num = driver->frames[driver->frame_cnt]->phrase[i];
		
		int idx = driver->phrase_cnt;
		// The phrase itself
		msf_phrase *phrase = driver->phrases[phrase_num];

		// Instrument for the current phrase at the current time
		msf_instrument *instrument = driver->instruments[phrase->inst[driver->phrase_cnt]];
		
		if (phrase->note[driver->phrase_cnt] == -1 || phrase->note[driver->phrase_cnt] == 0xFF) // Note kill
		{
			msf_kill_channel(driver,i);
		}

		// New step, check for notes and commands
		if (new_step)
		{
			// If there is a delay, don't trigger the note, just set the delay value instead.	

			// TODO: Fix HOP not triggering note of new frame
			if (phrase->cmd[idx] == MSF_FX_HOP)
			{
				if (phrase->arg[idx] < driver->phrase_length)
				{
					driver->hop_queue = phrase->arg[idx];
				}
			}
			else if (phrase->cmd[idx] == MSF_FX_JUMP)
			{
				if (phrase->arg[idx] < driver->num_frames)
				{
					driver->jump_queue = phrase->arg[idx];
				}
			}
			else if(phrase->cmd[idx] == MSF_FX_KILL)
			{
				if (phrase->arg[idx] == 0)
				{
					msf_kill_channel(driver,i);
				}
				driver->note_cut[i] = phrase->arg[idx];
			}
			else if (phrase->cmd[idx] == MSF_FX_SPEED)
			{
				driver->speed = phrase->arg[idx];
			}
			else if (phrase->cmd[idx] == MSF_FX_DELAY && phrase->arg[idx] > 0)
			{
				driver->note_delay[i] = phrase->arg[idx];
			}
			if (driver->note_delay[i] == 0 && phrase->inst[idx] != -1)
			{
				msf_trigger_note(driver,i,instrument,phrase->note[idx]);
			}
			if (phrase->cmd[idx] == MSF_FX_OUTPUT)
			{
				//printf("Output command\n");
				driver->amp_l[i] = ((phrase->arg[idx] & 0xF0) >> 4) / 16.0;
				driver->amp_r[i] = (phrase->arg[idx] & 0x0F) / 16.0;
			//	printf("Amplitude: %f\n",driver->amp_l[i]);
				poly_set_R_amp(i,driver->amp_r[i]);
				poly_set_L_amp(i,driver->amp_l[i]);
			}
		}
		msf_drv_inc_ll(driver, i);

		// Step through note delay
		if (driver->note_delay[i] > 0)
		{
			driver->note_delay[i]--;
			if (driver->note_delay[i] == 0)
			{
				msf_trigger_note(driver,i,driver->instruments[phrase->inst[driver->phrase_cnt]],driver->phrases[phrase_num]->note[driver->phrase_cnt]);
			}
		}
		if (driver->note_cut[i] > 0)
		{
			driver->note_cut[i]--;
			if (driver->note_cut[i] == 0) // note cut just occured
			{
				msf_kill_channel(driver,i);
			}
		}
		
		//  ------------------------------------------------------------------------------
		// | Commit information loaded from instrument data / runtime data to synthesizer |
		//  ------------------------------------------------------------------------------
		
		// Apply frequency offset from macro LL
		if (driver->pitch[i] != NULL)
		{
			driver->freq[i] += ((float)driver->pitch[i]->value / MSF_PITCH_DIV);
		}
		
		int arp_off = 0;
		if (driver->arp[i] != NULL)
		{
			arp_off = driver->arp[i]->value;
		}
		
		// Set the channel frequency
		// Considering: frequency from (note + arp offset + transpose) + pitch bend sum
		poly_set_freq(i,(driver->frames[driver->frame_cnt]->tune[i] / MSF_TUNE_DIV) + msf_get_freq(driver->note[i] + arp_off + driver->frames[driver->frame_cnt]->transpose[i]) + driver->freq[i]);
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

// Within 10 characters prints the channel state
void msf_print_channel_state(msf_driver *driver, int chan)
{
	char *notestr = "  ";
	char cmd = ' ';
	int phrase_index = driver->frames[driver->frame_cnt]->phrase[chan];
	int noteval = driver->phrases[phrase_index]->note[driver->phrase_cnt];
	noteval += driver->frames[driver->frame_cnt]->transpose[chan];
	int octave = noteval / 12;
	int instval = driver->phrases[phrase_index]->inst[driver->phrase_cnt];
	int argval = driver->phrases[phrase_index]->arg[driver->phrase_cnt];
	switch (noteval%12)
	{
		case NOTE_C:
			notestr = "C ";
			break;
		case NOTE_CS:
			notestr = "C#";
			break;
		case NOTE_D:
			notestr = "D ";
			break;
		case NOTE_DS:
			notestr = "D#";
			break;
		case NOTE_E:
			notestr = "E ";
			break;
		case NOTE_F:
			notestr = "F ";
			break;
		case NOTE_FS:
			notestr = "F#";
			break;
		case NOTE_G:
			notestr = "G ";
			break;
		case NOTE_GS:
			notestr = "G#";
			break;
		case NOTE_A:
			notestr = "A ";
			break;
		case NOTE_AS:
			notestr = "A#";
			break;
		case NOTE_B:
			notestr = "B ";
			break;
	}

	noteval -= driver->frames[driver->frame_cnt]->transpose[chan];
	if (noteval == 0)
	{
		notestr = "  ";
	}
	else if (noteval == 255)
	{
		notestr = "==";
	}
	switch (driver->phrases[phrase_index]->cmd[driver->phrase_cnt])
	{
		case MSF_FX_HOP:
			cmd = 'H';
			break;
		case MSF_FX_KILL:
			cmd = 'K';
			break;
		case MSF_FX_DELAY:
			cmd = 'D';
			break;
		case MSF_FX_OUTPUT:
			cmd = 'O';
			break;
		case MSF_FX_SPEED:
			cmd = 'S';
			break;
		case MSF_FX_JUMP:
			cmd = 'J';
			break;
	}

// Print the note

	textcolor(COL_DIM,COL_BLUE,COL_BLACK);
	printf("|");

	// Note and octave
	if (noteval > 0 && noteval < 255)
	{
		textcolor(COL_BRIGHT,COL_GREEN,COL_BLACK);
		printf("%s%i",notestr,octave);

	
	}
	else if (noteval == 0)
	{
		
		textcolor(COL_DIM,COL_GREEN,COL_BLACK);
		printf("%s ",notestr);
	}
	else if (noteval == 255)
	{
		
		textcolor(COL_DIM,COL_GREEN,COL_BLACK);
		printf("%s=",notestr);
	}

	// Instrument
	textcolor(COL_BRIGHT,COL_YELLOW,COL_BLACK);
	printf(" %02X ",instval);

	// Command
	textcolor(COL_BRIGHT,COL_CYAN,COL_BLACK);
	printf("%c",cmd);

	textcolor(COL_BRIGHT,COL_MAGENTA,COL_BLACK);
	if (cmd != ' ')
	{
		printf("%02X",argval);
	}
	else
	{
		printf("  ");
	}

	//
}

void msf_spill(msf_driver *driver)
{	
	for (int i = 0; i < driver->num_channels; i++)
	{
		msf_print_channel_state(driver,i);
	}
	textcolor(COL_DIM,COL_BLUE,COL_BLACK);
	printf("|\n");

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
		free(driver->note_cut);
		free(driver->note_delay);
		if (driver->name != NULL)
		{
			free(driver->name);
		}
		if (driver->author != NULL)
		{
			free(driver->author);
		}
	}
	free(driver);
}

#define MSF_MAX_LINELENGTH 65536

// Returns a dynamic array of the values from the delimited list
int *msf_get_line_values(const char *line)
{
	return malloc(sizeof(int));
}

// Returns the rest of line if line starts with word. If not,
// it returns null.
char *msf_get_entry(const char *word, const char *l)
{
	// Find length of the word
	int wordlen = 0;
	
	char *line = (char*)malloc(sizeof(char) * MSF_MAX_LINELENGTH);
	strncpy(line,l,MSF_MAX_LINELENGTH);
	
	for (int i = 0; i < MSF_MAX_LINELENGTH; i++)
	{
		if (word[i] == '\0' || word[i] == '\n')
		{
			wordlen = i;
			break;
		}
	}
	
	// Strip linebreak into a harmless space
	for (int i = 0; i < MSF_MAX_LINELENGTH; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
		}
		if (line[i] == '\0')
		{
			break;
		}
	}
	for (int i = 0; i < wordlen; i++)
	{
		if ((word[i] | 0x20) != (line[i] | 0x20))
		{
			free(line);
			return NULL;
		}
	}
	
	char *ret = (char*)malloc(sizeof(char) * MSF_MAX_LINELENGTH);
	strncpy(ret,&line[wordlen],MSF_MAX_LINELENGTH-wordlen);
	free(line);
	return ret;
}

// Choices:
// 0 duty
// 1 amp
// 2 pitch
// 3 arp
int msf_set_ll_param(msf_driver *driver, char *check, int choice)
{
	char *numcpy = malloc(sizeof(char) * 8); // Copy a fragment of the line to get the size
	numcpy = strncpy(numcpy,check,7);
	numcpy[7] = '\0'; // Just in case
	char *token = strtok(numcpy,MSF_DELIMITERS);
	int instnum = (int)strtoul(token,NULL,0);
	free(numcpy);
	token = NULL;
	msf_instrument *inst = driver->instruments[instnum];
	msf_ll *ll = NULL;
	int offset = 0;
	switch (choice)
	{
		case 0:
			ll = inst->duty_macro;
			offset = 0;
			break;
		case 1:
			ll = inst->amp_macro;
			offset = -128;
			break;
		case 2:
			ll = inst->pitch_macro;
			offset = -128;
			break;
		case 3:
			ll = inst->arp_macro;
			offset = -128;
			break;
	}
	if (ll != NULL)
	{
		msf_destroy_ll(ll);
	}
	
	ll = msf_parse_ll(check,offset,2);
	switch (choice)
	{
		case 0:
			inst->duty_macro = ll;
			break;
		case 1:
			inst->amp_macro = ll;
			break;
		case 2:
			inst->pitch_macro = ll;
			break;
		case 3:
			inst->arp_macro = ll;
			break;
	}
	free(check);
	return 1;
}

// Builds the driver; once this has happened handle_line is used only
msf_driver *msf_handle_driver_line(char *line)
{
	msf_driver* driver = NULL;
	// Initialize MSF driver
	char *check = NULL;
	check = msf_get_entry("init ",line);
	if (check != NULL) 
	{
		int count = 0;
		char *token = NULL;
		token = strtok(check,MSF_DELIMITERS);
		int speed = 6;
		int loopback = 0;
		int num_frames = 32;
		int num_channels = 8;
		int num_phrases = 8;
		int phrase_length = 64;
		int num_instruments = 16;
		if (token == NULL)
		{
			free(check);
			return 0;
		}
		while (token != NULL && count < 7)
		{
			switch (count)
			{
				case 0:
					speed = (int)strtoul(token,NULL,0);
					break;
				case 1:
					loopback = (int)strtoul(token,NULL,0);
					break;
				case 2:
					num_frames = (int)strtoul(token,NULL,0);
					break;
				case 3:
					num_channels = (int)strtoul(token,NULL,0);
					break;
				case 4:
					num_phrases = (int)strtoul(token,NULL,0);
					break;
				case 5:
					phrase_length =(int)strtoul(token,NULL,0);
					break;
				case 6:
					num_instruments = (int)strtoul(token,NULL,0);
					break;
			}
			token = strtok(NULL,MSF_DELIMITERS);
			count++;
		}
		printf("-init with %i %i %i %i %i %i %i ...",speed,loopback,num_frames,num_channels,
			num_phrases,phrase_length,num_instruments);
		driver = msf_init_special(speed,num_frames,num_channels,num_phrases,phrase_length,
			num_instruments);
		
		printf("Got driver at 0x%i.\n",(unsigned int)driver);
		driver->loopback = loopback;
		if (check != NULL)
		{
			free(check);
		}
	}
	return driver;
}

unsigned int msf_handle_line(msf_driver *driver, char *line)
{
	char *check;
	/* Check holds the result of seeing if the line begins with a property
	that is being seeked. If it matches, check contains the rest *after*
	the property tag. If it doesn't, it returns NULL. 

	Since this is not the fastest thing in the world, the potentially
	biggest operations come first here. 
	*/
	

	// Check if it's a frame definition

	check = msf_get_entry("#",line); // allow comments
	if (check != NULL) 
	{
		free(check); 
		return 1; 
	}
	check = msf_get_entry("//",line);
	if (check != NULL)
	{
		free(check);
		return 1;
	}

	if (driver != NULL && driver->init == 1)
	{
		// Metadata -- DON'T FREE CHECK, we are using that for the names!
		check = msf_get_entry("name is ",line);
		if (check != NULL)
		{ 
			if (driver->name != NULL)
			{
				printf("Warning: Name redefinition");
				driver->name = check; 
				return 2;
			}
			driver->name = check; 
			printf("-Put name.\n");
			return 1;
		}
		
		check = msf_get_entry("author is ",line);
		if (check != NULL)
		{
			if (driver->author != NULL)
			{
				printf("Warning: Author redefinition");
				driver->author = check;
				return 2;
			}
			driver->author = check; 
			printf("-Put author.\n");
			return 1;
		}	

		check = msf_get_entry("instrument ",line);
		if (check != NULL)
		{		
			char *token = strtok(check,MSF_DELIMITERS);
			int instnum = (int)strtoul(token,NULL,0);
			token = strtok(NULL,MSF_DELIMITERS); // skip the "is"
			if (token == NULL)
			{
				free(check);
				return 0;
			}
			token = strtok(NULL,MSF_DELIMITERS);
			msf_instrument *inst = driver->instruments[instnum];
			for (int i = 0; i < 3; i++)
			{
				if (token == NULL)
				{
					break;
				}
				switch (i)
				{
					case 0:
						inst->type = (int)strtoul(token,NULL,0);
						break;
					case 1:
						inst->left_amp = (float)strtoul(token,NULL,0) / 255.0;
						break;
					case 2:
						inst->right_amp = (float)strtoul(token,NULL,0) / 255.0;
						break;
				}

				token = strtok(NULL,MSF_DELIMITERS);
			}
			free(check);
			return 1;
		}

		// Parsing instrument parameters
		check = msf_get_entry("duty of instrument ",line);
		if (check != NULL)
		{
			msf_set_ll_param(driver,check,0);
		}

		// Parsing instrument parameters
		check = msf_get_entry("amp of instrument ",line);
		if (check != NULL)
		{
			msf_set_ll_param(driver,check,1);
		}

			// Parsing instrument parameters
		check = msf_get_entry("pitch of instrument ",line);
		if (check != NULL)
		{
			msf_set_ll_param(driver,check,2);
		}
			// Parsing instrument parameters
		check = msf_get_entry("arp of instrument ",line);
		if (check != NULL)
		{
			msf_set_ll_param(driver,check,3);
		}

		

		// Frame data
		check = msf_get_entry("frame ",line);
		if (check != NULL)
		{
			// Get the length of the original substring check and duplicate it
			
			// Go through it token by token with multiple delimiters in case
			// some mega marny thought it was a good idea to use underscores
			// or something dumb like that
			char *token = strtok(check,MSF_DELIMITERS); 
			int framenum = (int)strtoul(token,NULL,0);
			token = strtok(NULL,MSF_DELIMITERS); // skip the "is"
			if (token == NULL)
			{
				free (check);
				return 0;
			}
			int channel = 0;
			token = strtok(NULL,MSF_DELIMITERS); // Start capturing numbers
			while (token != NULL && channel < driver->num_channels)
			{
				unsigned long value = strtoul(token,NULL,0);
				int tune = ((unsigned char)((value >> 16) & 0xFF) - 128);
				int transpose = ((unsigned char)((value >> 8) & 0xFF) - 128);
	
				driver->frames[framenum]->phrase[channel] = (unsigned char)(value & 0xFF);
				driver->frames[framenum]->transpose[channel] = (transpose == -128)?(0):((int)transpose);
				driver->frames[framenum]->tune[channel] = (tune == -128)?(0):((int)tune);
	
				token = strtok(NULL,MSF_DELIMITERS);
				channel++;
			}
			printf("-Put frame %i\n",framenum);
	
			free(check);
			return 1;
		}
	
		// Define a phrase - the most complicated!
		check = msf_get_entry("phrase ",line);
		if (check != NULL)
		{
			char *token = strtok(check,MSF_DELIMITERS);
			int phrasenum = (int)strtoul(token,NULL,0);
			token = strtok(NULL,MSF_DELIMITERS); // skip the "is"
			if (token == NULL)
			{
				free(check);
				return 0;
			}
			msf_phrase *phraseptr = driver->phrases[phrasenum];
			int stepnum = 0;
			token = strtok(NULL,MSF_DELIMITERS);
			while (token != NULL && stepnum < phraseptr->length)
			{
				unsigned long value = strtoul(token,NULL,0);
				int arg = ((unsigned char)((value >> 24) & 0xFF));
				int cmd = ((unsigned char)((value >> 16) & 0xFF));
				int inst = ((unsigned char)((value >> 8) & 0xFF));
				int note = ((unsigned char)((value) & 0xFF));

			

				phraseptr->note[stepnum] = (unsigned char)(value & 0xFF);
				phraseptr->inst[stepnum] = inst;
				phraseptr->cmd[stepnum] = cmd;
				phraseptr->arg[stepnum] = arg;
				token = strtok(NULL,MSF_DELIMITERS);
				stepnum++;
			}
			if (phraseptr->used != 0)
			{
				printf("Warning: Redefinition of phrase #%i",phrasenum);
				free(check);
				return 2;
			}
	
			phraseptr->used = 1;
			printf("-Put phrase %i\n",phrasenum);
			free(check);
			return 1;
		}
	}
	
	if (check == NULL)
	{
		return 0;
	}
	return 0;
}

msf_driver *msf_load_file(const char *fname)
{
	// TODO: make this section a lot better	
	FILE *file = fopen(fname, "r");
	if (file == NULL)
	{
		printf("Failed to load MSF file. Aborting.\n");
		return NULL;
	}
	
	int line_number = 1;
	
	// Allocate for one line, ready to realloc if needed
	int buffer_size = MSF_MAX_LINELENGTH;
	char *line = (char*)malloc(MSF_MAX_LINELENGTH* sizeof(char*));
	
	msf_driver *driver = NULL;
	// Handle each line, taking data from it as is appropriate
	while (fgets(line, MSF_MAX_LINELENGTH, file))
	{
		if (driver == NULL)
		{
			driver = msf_handle_driver_line(line);
		}
		else
		{
			unsigned long result = msf_handle_line(driver,line);
		
			if (result == 0)
			{
				printf("Ignoring line %i.\n",line_number);
			}
			else if (result == 2)
			{
				printf(" at line %i.\n",line_number);
			}
			else if (result > 8)
			{
				driver = (msf_driver*)result;
			}
		}
			
		printf("\n");
		line_number++;
	}
	printf("Name: %s\n",driver->name);
	printf("By: %s\n",driver->author);
	fclose(file);
	free(line);
	printf("Starting.\n");
	return driver;	
}
