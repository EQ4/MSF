#include "editor/render.h"
#include "editor/colors.h"
#include "editor/dimensions.h"
#include "editor/audio.h"

ALLEGRO_BITMAP *main_buffer;
ALLEGRO_DISPLAY *display;
ALLEGRO_FONT *font;
ALLEGRO_FONT *fontbold;
unsigned int window_mode;

// Calling this twice is fine - it will check if the display / buffer
// already has been created and will rebuild it if needed.
void init_render(void)
{
	if (font)
	{
		al_destroy_font(font);
	}
	font = al_load_ttf_font("./gohufont.fon",11,ALLEGRO_TTF_MONOCHROME);
	if (fontbold)
	{
		al_destroy_font(fontbold);
	}
	fontbold = al_load_ttf_font("./gohubold.fon",11,ALLEGRO_TTF_MONOCHROME);
	al_set_new_display_flags(window_mode);
	if (display)
	{
		al_destroy_display(display);
	}
	display = al_create_display(win_w,win_h);
	if (main_buffer)
	{
		al_destroy_bitmap(main_buffer);
	}
	main_buffer = al_create_bitmap(win_w,win_h);
	al_register_event_source(event_queue, al_get_display_event_source(display));
}

// j: row being drawn
// bx, by: render offsets
void render_hilights(int j, int bx, int by)
{
	if (by < char_h + 0.5)
	{
		return;
	}
	if (j == driver->phrase_cnt)
	{
		al_draw_filled_rectangle(bx, by - char_h - 0.5, 
			bx + (12 * char_w), by - 1.0, MSF_COL_CURRENTLINE);
	}
	else if (j % hilight2 == 0)
	{
		al_draw_filled_rectangle(bx, by - char_h - 0.5, 
			bx + (12 * char_w), by - 1.0, MSF_COL_HILIGHT2);
	}
	else if (j % hilight1 == 0)
	{
		al_draw_filled_rectangle(bx, by - char_h - 0.5, 
			bx + (12 * char_w), by - 1.0, MSF_COL_HILIGHT1);
	}
}

// j: row being drawn
// bx, by: render offsets
// str: string to modify or print 
void render_notetext(int j, int bx, int by, char *str, msf_phrase *phrase)
{
	ALLEGRO_COLOR col = MSF_COL_NOTE;
	if (str[0] == '=')
	{
		col = MSF_COL_CUT;
	}

	msf_get_channel_note(phrase, j, str);
	al_draw_text(font, col,bx,by,0,str);
	bx += (4 * char_w);

	msf_get_channel_inst(phrase, j, str);
	al_draw_text(font, MSF_COL_INST,bx,by,0,str);
	bx += (3 * char_w);

	msf_get_channel_cmd(phrase, j, str);
	al_draw_text(font, MSF_COL_CMD,bx,by,0,str);
	bx += (2 * char_w);

	msf_get_channel_arg(phrase, j, str);
	al_draw_text(font, MSF_COL_ARG,bx,by,0,str);
}

void render_phrase(int x, int y, char *str, msf_phrase *phrase)
{
	for (int j = 0; j < phrase->length; j++)
	{
		int by = y + char_h + (char_h * j);
		by -= driver->phrase_cnt * char_h; // Current line at the top
		// Don't render below window when not needed
		if (by > win_h + char_h)
		{
			//break;
		}
					
		render_hilights(j, x, by);	
		render_notetext(j, x, by, str, phrase);
	}
}

void update_display(void)
{
	al_set_target_backbuffer(display);
	al_draw_bitmap(main_buffer,0,0,0);
	al_flip_display();
	al_set_target_bitmap(main_buffer);
}
