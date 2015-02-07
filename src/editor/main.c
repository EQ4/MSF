/*

MSF Editor GUI
Michael Moffitt 2014
------------------------------------------------------------------------------

*/

#include "editor/includes.h"
#include <stdio.h>

#include "editor/colors.h"
#include "editor/audio.h"
#include "editor/render.h"
#include "editor/dimensions.h"
#include "driver.h"

#define NUM_FRAGMENTS 2
#define SIZE_FRAGMENT 4096
#define RATE 44100

#define WIN_W 640
#define WIN_H 480

void clear_pointers(void)
{
	driver = NULL;
	stream = NULL;
	display = NULL;
	main_buffer = NULL;
	event_queue = NULL;
}

void set_defaults(void)
{
	win_w = WIN_W;
	win_h = WIN_H;
	char_w = CHAR_W;
	char_h = CHAR_H;
	hilight1 = HILIGHT1;
	hilight2 = HILIGHT2;
	window_mode = MODE_WINDOW;

	num_samples = NUM_SAMPLES;
	audio_rate = AUDIO_RATE;
	num_fragments = NUM_FRAGMENTS;
	size_fragment = SIZE_FRAGMENT;

	scroll_x = 0;
	scroll_y = 0;

}

void init_event_queue(void)
{
	if (event_queue)
	{
		al_destroy_event_queue(event_queue);
	}
	event_queue = al_create_event_queue();
}


// TODO: init without song
void init_msf(char *fname)
{
	if (driver)
	{
		msf_shutdown(driver);
	}
	driver = msf_load_file(fname);
	printf("MSF driver is at %08X\n",(unsigned int)driver);
	driver->print_notes = 0;
}

void init(void)
{
	al_init();
	al_install_audio();
	al_init_acodec_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	
	set_defaults();
	init_event_queue();
	init_render();
	init_audio();
}

int main(int argc, char *argv[])
{

	int quit;
	if (argc == 1)
	{
		printf("Usage: msfplay songname.msf\n");
		return 1;
	}
	printf("Clearing pointers\n");
	clear_pointers();
	printf("Setting defaults\n");
	set_defaults();
	printf("Calling init()\n");
	init();
	printf("Calling init_msf() with %s...\n",argv[1]);
	init_msf(argv[1]);
	printf("...ok\n");
	if (driver == NULL)
	{
		return -1;
	}
	printf("Beginning\n");
	int song_timer = 0;

	// Initialization boilerplate

	quit = 0;
	

	int draw_h = 0;

	char *notestr = (char *)malloc(sizeof(char) * 5);
	int16_t *frame;
	for (;;)
	{
		ALLEGRO_EVENT event;
		if (!al_is_event_queue_empty(event_queue))
		{
			al_get_next_event(event_queue, &event);
			switch(event.type)
			{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				printf("Exiting\n");
				quit = 1;
				break;
			case ALLEGRO_EVENT_DISPLAY_RESIZE:
				if (event.display.source == display)
				{
					al_destroy_bitmap(main_buffer);
					win_w = event.display.width;
					win_h = event.display.height;
					main_buffer = al_create_bitmap(win_w,win_h);
					al_resize_display(display, win_w, win_h);
				}
				al_acknowledge_resize(event.display.source);
				break;
			case ALLEGRO_EVENT_AUDIO_STREAM_FRAGMENT:
				// Time to get the next sample
				frame = (int16_t *)al_get_audio_stream_fragment(stream);
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
				break;
			case ALLEGRO_EVENT_AUDIO_STREAM_FINISHED:
				printf("Stream has completed.\n");
				al_drain_audio_stream(stream);
				break;
			}
		}

		al_clear_to_color(al_map_rgb(0,0,0));
		for (int i = 0; i < driver->num_channels; i++)
		{
			render_phrase(
				(char_w * MSF_RENDER_TXTLEN * i),
				win_h / 2,
				notestr,
				msf_get_current_phrase(driver,i));
			

		}
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
