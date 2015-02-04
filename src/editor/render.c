#include "editor/render.h"

// j: row being drawn
// basex, basey: render offsets
void msf_render_hilights(int j, int basex, int basey)
{
	if (j == driver->phrase_cnt)
	{
		al_draw_filled_rectangle(basex, basey - char_h - 0.5, 
			basex + (12 * char_w), basey - 1.0, MSF_COL_CURRENTLINE);
	}
	else if (j % hilight2 == 0)
	{
		al_draw_filled_rectangle(basex, basey - char_h - 0.5, 
			basex + (12 * char_w), basey - 1.0, MSF_COL_HILIGHT2);
	}
	else if (j % hilight1 == 0)
	{
		al_draw_filled_rectangle(basex, basey - char_h - 0.5, 
			basex + (12 * char_w), basey - 1.0, MSF_COL_HILIGHT1);
	}
}

// j: row being drawn
// basex, basey: render offsets
// notestr: string to modify or print 
void msf_render_notetext(int j, int basex, int basey, char *notestr, msf_phrase *phrase)
{
	ALLEGRO_COLOR col = MSF_COL_NOTE;
	if (notestr[0] == '=')
	{
		col = MSF_COL_CUT;
	}

	msf_get_channel_note(phrase, j, notestr);
	al_draw_text(font, col,basex,basey,0,notestr);
	basex += (4 * char_w);

	msf_get_channel_inst(phrase, j, notestr);
	al_draw_text(font, MSF_COL_INST,basex,basey,0,notestr);
	basex += (3 * char_w);

	msf_get_channel_cmd(phrase, j, notestr);
	al_draw_text(font, MSF_COL_CMD,basex,basey,0,notestr);
	basex += (2 * char_w);

	msf_get_channel_arg(phrase, j, notestr);
	al_draw_text(font, MSF_COL_ARG,basex,basey,0,notestr);
}

void msf_render_phrases(int x, int y, char *notestr)
{
	for (int i = 0; i < driver->num_channels; i++)
	{
		msf_phrase *phrase = msf_get_current_phrase(driver,i);
		int basex = x + (char_w * MSF_RENDER_TXTLEN * i);
		for (int j = 0; j < phrase->length; j++)
		{
			int basey = y + char_h + (char_h * j);
			basey -= driver->phrase_cnt * char_h;
			basey += phrase->length * char_h / 2;

			// Don't render below window when not needed
			if (j > (win_h / char_h) + 1)
			{
				break;
			}
						
			msf_render_hilights(j, basex, basey);	
			msf_render_notetext(j, basex, basey, notestr, phrase);
		}
	}
}
