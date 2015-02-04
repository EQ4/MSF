#ifndef RENDER_H
#define RENDER_H

#define MSF_RENDER_TXTLEN 12

#include "editor/includes.h"

void msf_render_hilights(int j, int basex, int basey);
void msf_render_notetext(int j, int basex, int basey, char *notestr, msf_phrase *phrase);
void msf_render_phrases(int x, int y, char *notestr);

#endif
