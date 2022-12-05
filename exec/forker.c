#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int p[2];
	char *cat[] = { "/bin/cat", "exec.c", NULL };
	char *wc[] = { "/usr/bin/wc", "-l", NULL };
	int ret;

	ret = pipe(p);
	if (ret < 0)
		printf("pipe failed \n");
	ret = fork();
	if (ret < 0)
		printf("fork failed \n");
	if (ret == 0)
	{
		// cat
		dup2(p[1], STDOUT_FILENO);
		// close(p[0]);
		execve(cat[0], cat, NULL);

		// write(STDOUT_FILENO, "hello world !\n", 15);
		// write(STDOUT_FILENO, "hello world !", 14);
		return (0);
	}

	// wc
	dup2(p[0], STDIN_FILENO);
	// close(p[1]);
	execve(wc[0], wc, NULL);
	
	// char buf[255];
	// read(STDIN_FILENO, buf, 14);
	// write(1, "received: ", 11);
	// write(1, buf, 14);
	return 0;
}
