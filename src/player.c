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
	msf_driver driver;
	printf("MSF init sequence starting.\n");
	msf_init(&driver);
	
	msf_load_file(&driver,"/home/moffitt/test.msf");
	
//	for (int i = 0; i < 6*64*4; i++)
//	{
//		usleep(16000);
//		
//		msf_step(&driver);
//		msf_spill(&driver);
//	}
	printf("Killing driver now.\n");
	msf_shutdown(&driver);
	return 0;
}
