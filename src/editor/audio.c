#include "editor/audio.h"

unsigned int num_samples;
unsigned int audio_rate;
unsigned int num_fragments;
unsigned int size_fragment;
unsigned int music_timer;

ALLEGRO_AUDIO_STREAM *stream;
msf_driver *driver;

void init_audio(void)
{
	al_reserve_samples(num_samples); // Sets up the default mixer
	// Set up the audio stream and mixer attachment
	if (stream)
	{
		if (al_get_mixer_attached(al_get_default_mixer()))
		{
			al_detach_mixer(al_get_default_mixer());
		}
		al_destroy_audio_stream(stream);
	}

	stream = al_create_audio_stream(
		num_fragments,
		size_fragment,
		audio_rate,
		AUDIO_DEPTH,
		CHANNEL_CONF);

	al_attach_audio_stream_to_mixer(stream, al_get_default_mixer());

	al_register_event_source(event_queue, 
		al_get_audio_stream_event_source(stream));

}

void audio_fill_buffer()
{
	int16_t *frame = (int16_t *)al_get_audio_stream_fragment(stream);
	if (!frame == NULL)
	{
		for (int i = 0; i < SIZE_FRAGMENT; i++)
		{	
			music_timer++;
			// Maintain timings for the sound engine regardless of FPS
			if (music_timer > 735)
			{
				music_timer = 0;
				msf_step(driver);
			}
			poly_next_frame((int16_t *)(frame + (2*i)));
		}
		al_set_audio_stream_fragment(stream, (void *)frame);
	}
}
