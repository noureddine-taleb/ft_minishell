#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("pid=%d sid=%d pgid=%d\n", getpid(), getsid(getpid()), getpgid(getpid()));
}
