/*

MSF Player
Michael Moffitt 2014
------------------------------------------------------------------------------
This is a simple example "client" to the MSF driver. 




*/

#include <stdio.h>
#include <stdlib.h>

#include "instrument.h"
#include "phrase.h"
#include "frame.h"
#include "driver.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_primitives.h>

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_AUDIO_STREAM *stream;
int quit;

#define NUM_FRAGMENTS 2
#define SIZE_FRAGMENT 1024
#define RATE 44100

int main(int argc, char *argv[])
{

	if (argc == 1)
	{
		printf("Usage: msfplay songname.msf\n");
		return 1;
	}

	const char *song;
	song = argv[1];
	msf_driver *driver = msf_load_file(song);
	if (driver == NULL)
	{
		return -1;
	}

	
	int song_timer = 0;

	// Initialization boilerplate
	al_init();
	al_install_audio();
	al_init_acodec_addon();
	al_init_primitives_addon();
	display = al_create_display(640,480);
	quit = 0;
	
	// Set up the audio stream and mixer attachment
	al_reserve_samples(1); // Sets up the default mixer
	
	stream = al_create_audio_stream(
		NUM_FRAGMENTS,
		SIZE_FRAGMENT,
		RATE,
		ALLEGRO_AUDIO_DEPTH_INT16,
		ALLEGRO_CHANNEL_CONF_2);
	al_attach_audio_stream_to_mixer(stream, al_get_default_mixer());

	// Set up event sources so the stream can request more sample frames, and we
	// can also close the window.
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_audio_stream_event_source(stream));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	driver->print_notes = 1;

	int pos = 0;

	int draw_h = 0;

	while(!quit)
	{
		ALLEGRO_EVENT event;
		if (!al_is_event_queue_empty(event_queue))
		{
			al_get_next_event(event_queue, &event);
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				printf("Exiting\n");
				quit = 1;
			}
			else if (event.type == ALLEGRO_EVENT_AUDIO_STREAM_FRAGMENT)
			{
				// Time to get the next sample
				int16_t *frame = (int16_t *)al_get_audio_stream_fragment(stream);
				if (!frame == NULL)
				{
					draw_h = 0;
					for (int i = 0; i < SIZE_FRAGMENT; i++)
					{	
						song_timer++;
						if (song_timer > 735)
						{
							song_timer = 0;
							msf_step(driver);
						}
						poly_next_frame((int16_t *)(frame + (2*i)));
						if (*frame > 0)
						{
							draw_h += *frame;
						}
						else
						{
							draw_h -= *frame;
						}
					}
					al_set_audio_stream_fragment(stream, (void *)frame);
				}
			}
			else if (event.type == ALLEGRO_EVENT_AUDIO_STREAM_FINISHED)
			{
				printf("Stream has completed.\n");
				al_drain_audio_stream(stream);
			}
		}
		draw_h = (int)(240.0 * draw_h / (32768.0));
		draw_h = draw_h / SIZE_FRAGMENT;
		al_draw_line(pos, 0, pos, 480, al_map_rgb(0,0,0), 1);
		al_draw_line(pos, 240 - draw_h,
			pos,240 + draw_h,al_map_rgb(255,255,255),1);

		pos++;
		if (pos == 640)
		{
			pos = 0;
		}
		al_flip_display();

	}
	//poly_shutdown();
	//al_destroy_audio_stream(stream);
	//al_destroy_display(display);
	//al_destroy_event_queue(event_queue);
	msf_shutdown(driver);
	return 0;
}
