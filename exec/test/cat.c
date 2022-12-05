#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	close(0);
	int written = write(1, "Hello, world\n", 15);
	fprintf(stderr, "cat%d writes: %d\n", STATUS, written);
	#ifdef SLEEP
	sleep(1);
	#endif
	return STATUS;
}