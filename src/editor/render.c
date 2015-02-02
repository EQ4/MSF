#include "editor/render.h"

void msf_render_phrases(int x, int y, char *notestr)
{
	for (int i = 0; i < driver->num_channels; i++)
	{
		for (int j = 0; j < (win_h / char_h) + 1; j++)
		{
			msf_phrase *phrase = msf_get_current_phrase(driver,i);
			int basex = x + (char_w * 12 * i);
			int basey = y + char_h + (char_h * j);
			basey -= driver->phrase_cnt * char_h;
			basey += phrase->length * char_h / 2;
			if (j >= phrase->length)
			{
				break;
			}
			msf_get_channel_note(phrase, j, notestr);
			ALLEGRO_COLOR col = MSF_COL_NOTE;
			if (notestr[0] == '=')
			{
				col = MSF_COL_CUT;
			}

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
	}
}
