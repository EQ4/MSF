#include <stdioh>
#include "src/include/instrument.h"

int main(int argc, char *argv[])
{
	msf_instrument *test = msf_create_instrument();
	test->type = 18;
	printf("The type of wave is %d.\n",test->type);
	msf_destroy_instrument(test);
	return 0;
}

