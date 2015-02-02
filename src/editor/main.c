/*

MSF Editor GUI
Michael Moffitt 2014
------------------------------------------------------------------------------

*/

#include "editor/includes.h"
#include <stdio.h>

#include "editor/colors.h"

int quit;

#define NUM_FRAGMENTS 2
#define SIZE_FRAGMENT 2048
#define RATE 44100

#define WIN_W 320
#define WIN_H 240

void update_display(void)
{
	al_set_target_backbuffer(display);
	al_draw_bitmap(main_buffer,0,0,0);
	al_flip_display();
	al_set_target_bitmap(main_buffer);
}

int init(void)
{
	al_init();
	al_install_audio();
	al_init_acodec_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_set_new_display_flags(ALLEGRO_RESIZABLE|ALLEGRO_WINDOWED);
	font = al_load_ttf_font("./gohufont.fon",11,ALLEGRO_TTF_MONOCHROME);
	fontbold = al_load_ttf_font("./gohubold.fon",11,ALLEGRO_TTF_MONOCHROME);
	
	win_w = WIN_W;
	win_h = WIN_H;

	char_w = 6;
	char_h = 9;

	hilight1 = 4;
	hilight2 = 16;

	display = al_create_display(win_w,win_h);
	main_buffer = al_create_bitmap(win_w,win_h);

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

	driver->print_notes = 0;

	scroll_x = 0;
	scroll_y = 0;
}

int main(int argc, char *argv[])
{

	if (argc == 1)
	{
		printf("Usage: msfplay songname.msf\n");
		return 1;
	}

	const char *song;
	song = argv[1];
	driver = msf_load_file(song);
	if (driver == NULL)
	{
		return -1;
	}

	
	int song_timer = 0;

	// Initialization boilerplate
	if (init() == 0)
	{
		msf_shutdown(driver);
		return -1;
	}
	quit = 0;
	
	// Set up the audio stream and mixer attachment

	int draw_h = 0;

	char *notestr = (char *)malloc(sizeof(char) * 5);
	for (;;)
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
			else if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
			{
				if (event.display.source == display)
				{
					al_destroy_bitmap(main_buffer);
					win_w = event.display.width;
					win_h = event.display.height;
					main_buffer = al_create_bitmap(win_w,win_h);
					al_resize_display(display, win_w, win_h);
				}
				al_acknowledge_resize(event.display.source);
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

		al_clear_to_color(al_map_rgb(0,0,0));

		msf_render_phrases(0,0,notestr);
		update_display();
		if (quit)
		{
			goto exit_lab;
		}
	}
exit_lab:
	//poly_shutdown();
	//al_destroy_audio_stream(stream);
	//al_destroy_display(display);
	//al_destroy_event_queue(event_queue);
	free(notestr);
	msf_shutdown(driver);
	return 0;
}
