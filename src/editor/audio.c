#include "editor/audio.h"

unsigned int num_samples;
unsigned int audio_rate;
unsigned int num_fragments;
unsigned int size_fragment;

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
	al_register_event_source(event_queue, al_get_audio_stream_event_source(stream));

}
