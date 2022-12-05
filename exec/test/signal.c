#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void handler(int signal)
{
	fprintf(stderr, "sig%d signal received %d\n", ID, signal);
}

int main()
{
	signal(SIGINT, handler);
	close(0);
	close(1);
	close(2);
	if (setsid())
	{
		perror("setsid");
		exit(1);
	}
	pause();
	fprintf(stderr, "sig%d bail out\n", ID);
	return 0;
}