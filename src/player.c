/*

MSF Player
Michael Moffitt 2014
------------------------------------------------------------------------------
This is a simple example "client" to the MSF driver. 




*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/instrument.h"
#include "../include/phrase.h"
#include "../include/frame.h"
#include "../include/driver.h"
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
	while(1)
	{
		usleep(16000);
		
		msf_step(driver);
//		msf_spill(driver);
	}
	printf("Killing driver now.\n");
	msf_shutdown(driver);
	return 0;
}
