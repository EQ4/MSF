#include "../include/player.h"

msf_player player;

void msf_init_special(int speed, int num_frames, int num_channels, int num_phrases, int phrase_length, int num_instruments)
{
	player.speed = speed;
	player.num_frames = num_frames;
	player.num_channels = num_channels;
	player.num_phrases = num_phrases;
	player.phrase_length = phrase_length;
	player.num_instruments = num_instruments;

// Reset state variables
	player.frame_cnt = 0;
	player.phrase_cnt = 0;
	player.phrase_adv = 0;

	player.frames = malloc(sizeof(msf_frame *) * num_frames);
	player.phrases = malloc(sizeof(msf_phrase *) * num_phrases);
	player.instruments = malloc(sizeof(msf_instrument *) * num_instruments);

	// Actually build the structs the above pointer arrays point to
	for (int i = 0; i < num_frames; i++)
	{
		player.frames[i] = msf_create_frame(num_channels);
	}

	for (int i = 0; i < num_phrases; i++)
	{
		player.phrases[i] = msf_create_phrase(phrase_length);
	}

	for (int i = 0; i < num_instruments; i++)
	{
		player.instruments[i] = msf_create_instrument();
		player.instruments[i]->amp_macro->value = 255; // Default to full blast
		//printf("Created instrument #%d at 0x%d.\n",i,(unsigned int)player.instruments[i]);
	}

	// Point these to the LL macros (one per channel);
	player.arp = malloc(num_channels * sizeof(msf_ll *));
	player.amp = malloc(num_channels * sizeof(msf_ll *));
	player.pitch = malloc(num_channels * sizeof(msf_ll *));
	player.duty = malloc(num_channels * sizeof(msf_ll *));
	for (int i = 0; i < num_channels; i++) // Null them out to avoid confusion
	{
		player.arp[i] = NULL;
		player.amp[i] = NULL;
		player.pitch[i] = NULL;
		player.duty[i] = NULL;
	}
	player.init = 1;
	player.loopback = 0;
	player.track_length = 1;

	player.amp_l = malloc(sizeof(float *) * num_channels);
	player.amp_r= malloc(sizeof(float *) * num_channels);
	player.freq = malloc(sizeof(float *) * num_channels);
	player.note = malloc(sizeof(int *) * num_channels);

	// Initialize libPOLY6 with the parametres from above
	poly_init(16,2,44100,num_channels,NULL);
	for (int i = 0; i < num_channels; i++)
	{
		poly_init_generator(i,square,0.0,440 + (8*i));
	}
	poly_start();
}

// Simple shortcut init with some usable (but maybe too large) defaults
void msf_init()
{
	msf_init_special(
	MSF_DEFAULT_SPEED,
	MSF_NUM_FRAMES,
	MSF_NUM_CHANNELS,
	MSF_NUM_PHRASES,
	MSF_PHRASE_LENGTH,
	MSF_NUM_INSTRUMENTS);
}

void msf_step()
{
	int new_step = 0;

	if (player.phrase_adv == 0 && player.phrase_cnt == 0)
	{
		new_step = 1;
	}
	if (player.phrase_adv == player.speed) // Time to go to next step
	{
		player.phrase_adv = 0;
		player.phrase_cnt++;
		new_step = 1;
	}
	player.frames[0]->tune[3] = 16;
	if (player.phrase_cnt == player.phrase_length) // End of phrase
	{
		player.frame_cnt++;
		player.phrase_cnt = 0;
		player.phrase_adv = 0;
		printf("Moving to frame %d, channel 0 has phrase %d.\n",player.frame_cnt,player.frames[player.frame_cnt]->phrase[0]);
	}
	if (player.frame_cnt == player.track_length) // End of song
	{
		player.phrase_cnt = 0;
		player.phrase_adv = 0;
		player.frame_cnt = player.loopback;
	}
	
	for (int i = 0; i < player.num_channels; i++)
	{
		// Pull the phrase number for channel i from the current frame
		int phrase_num = player.frames[player.frame_cnt]->phrase[i];
		// The phrase itself
		msf_phrase *phrase = player.phrases[phrase_num];

		// Instrument for the current phrase at the current time
		msf_instrument *instrument = player.instruments[phrase->inst[player.phrase_cnt]];
		
		if (phrase->note[player.phrase_cnt] == -1) // Note kill
		{
			poly_set_amplitude(i,0);
			player.amp_l[i] = 0;
			player.amp_r[i] = 0;
			player.note[i] = -1;
		}
		if (new_step && phrase->note[player.phrase_cnt] != 0 && phrase->inst[player.phrase_cnt] != -1) // If there is a note to set
		{
		//	printf("NOTE ON %d! -Value %d inst %d.\n",i,phrase->note[player.phrase_cnt],phrase->inst[player.phrase_cnt]);
			// Set the note
			// Reset our macro traversal
			player.arp[i] = instrument->arp_macro;
			//printf("New arp macro: 0x%d\n",player.arp[i]);
			player.amp[i] = instrument->amp_macro;
			player.pitch[i] = instrument->pitch_macro;
			player.duty[i] = instrument->duty_macro;
			player.note[i] = phrase->note[player.phrase_cnt];
			player.amp_l[i] = instrument->left_amp;
			player.amp_r[i] = instrument->right_amp;
			

			poly_set_R_amp(i,player.amp_r[i]);
			poly_set_L_amp(i,player.amp_l[i]);
			
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
				// The rest will come once libpoly supports them properly
			}
		}
		else
		{
			// Advance the macro LLs
			if (player.arp[i] != NULL && player.arp[i]->next != NULL)
			{
			//	printf("Advancing arp LL\n");
				player.arp[i] = player.arp[i]->next;	
			}
			if (player.amp[i] != NULL && player.amp[i]->next != NULL)
			{
			//	printf("Advancing amp LL\n");
				player.amp[i] = player.amp[i]->next;
			}
			if (player.pitch[i] != NULL && player.pitch[i]->next != NULL)
			{
				player.pitch[i] = player.pitch[i]->next;
			}
			if (player.duty[i] != NULL && player.duty[i]->next != NULL)
			{
				player.duty[i] = player.duty[i]->next;
			}
		}
		if (player.duty[i] != NULL)
		{
			poly_set_duty(i,(player.duty[i]->value/255.0));
		}
		int arp_off = player.frames[player.frame_cnt]->transpose[i];
		if (player.arp[i] != NULL)
		{
			//printf("Setting arp_off to %d.\n",player.arp[i]->value);
			arp_off += player.arp[i]->value;
		}
		float pitch_off = player.frames[player.frame_cnt]->tune[i] / MSF_TUNE_DIV;
		if (player.pitch[i] != NULL)
		{
			pitch_off += player.pitch[i]->value;
		}
		player.freq[i] = msf_get_freq(player.note[i] + arp_off) + pitch_off;
		
		if (i == 0)
		{
			// printf("Frequency is %f.\n",player.freq[i]);
		}
		poly_set_freq(i,player.freq[i]);
		if (player.note[i] != -1 && player.amp[i] != NULL)
		{
			poly_set_amplitude(i,player.amp[i]->value/255.0);
		}
	}
	player.phrase_adv++;
}

void msf_spill()
{
	printf("%d\t%d\t%d\n",player.frame_cnt,player.phrase_cnt,player.phrase_adv);
}

void msf_shutdown()
{
	poly_stop();
	poly_shutdown();
	if (player.init == 1)
	{
		for (int i = 0; i < player.num_frames; i++)
		{
			//printf("----%d: Destroying frame 0x%d\n",i,(unsigned int)player.frames[i]);
			msf_destroy_frame(player.frames[i]);
		}
		for (int i = 0; i < player.num_phrases; i++)
		{
			//printf("----%d: Destroying phrase 0x%d\n",i,(unsigned int)player.phrases[i]);
			msf_destroy_phrase(player.phrases[i]);
		}
		for (int i = 0; i < player.num_instruments; i++)
		{
			printf("----%d: Destroying instrument 0x%d\n",i,(unsigned int)player.instruments[i]);
			msf_destroy_instrument(player.instruments[i]);
		}
		
		//printf("----Freeing frames\n");
		free(player.frames);
		//printf("----Freeing phrases\n");
		free(player.phrases);
		//printf("----Freeing instruments\n");
		free(player.instruments);
		//printf("----Freeing arp\n");
		free(player.arp);
		//printf("----Freeing amp\n");
		free(player.amp);
		//printf("----Freeing pitch\n");
		free(player.pitch);
		//printf("----Freeing note\n");
		free(player.note);
		//printf("----Freeing amp_l\n");
		free(player.amp_l);
		//printf("----Freeing amp_r\n");
		free(player.amp_r);
		//printf("----Freeing freq\n");
		free(player.freq);
		free(player.duty);
	}
}
