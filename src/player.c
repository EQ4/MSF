#include "../include/player.h"

msf_player player;

void msf_init_special(int speed, int num_frames, int num_channels, int num_phrases, int phrase_length, int num_instruments)
{
	player.speed = speed;
	player.num_frames = num_frames;
	player.num_channels = num_channels;
	player.num_phrases = num_phrases;
	player.phrase_lengt = phrase_length;
	player.num_instruments = num_instruments;

// Reset state variables
	player.frame_adv = 0;
	player.frame_cnt = 0;
	player.phrase_cnt = 0;

	player.frames = malloc(sizeof(msf_frame *) * num_frames);
	player.phrases = malloc(sizeof(msf_phrase *) * num_phrases);
	player.instruments = malloc(sizeof(msf_instrument *) * num_instruments);

	// Actually build the structs the above pointer arrays point to
	for (unsigned int i = 0; i < num_frames; i++)
	{
		player.frames[i] = malloc(sizeof(msf_frame));
		player.phrases[i] = malloc(sizeof(msf_phrase));
		player.instruments[i] = malloc(sizeof(msf_instrument));
	}

	// Point these to the arrays
	player.macros = malloc(sizeof(msf_ll *));

}

void msf_init()
{
	player.speed = 6;
	player.frame_adv = 0;
	player.frame_cnt = 0;
	player.phrase_cnt = 0;

	player.frames = malloc(sizeof(msf_frame) * MSF_NUM_FRAMES);
	player.phrases = malloc(sizeof(msf_phrase) * MSF_NUM_PHRASES);
	player.instruments = malloc(sizeof(msf_instrument) * MSF_NUM_INSTRUMENTS);

	

}
