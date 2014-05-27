/*

MSF Player
Michael Moffitt 2014
------------------------------------------------------------------------------
This is a simple example "client" to the MSF driver. 




*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "instrument.h"
#include "phrase.h"
#include "frame.h"
#include "driver.h"
int main(int argc, char *argv[])
{

/* 
	Let's play with ncurses
*/
	
	initscr();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	attron(A_UNDERLINE | COLOR_PAIR(1));
	mvprintw(32,32,"");
	printw("Hello World!");
	attroff(A_UNDERLINE | COLOR_PAIR(1));
	refresh();
	getch();
	endwin();

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
	while(1)
	{
		usleep(16000);
		
		msf_step(driver);
	}
	printf("Killing driver now.\n");
	msf_shutdown(driver);
	return 0;
}
