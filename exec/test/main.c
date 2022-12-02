#include "../minishell.h"
#include <stdlib.h>
#include <stdio.h>

// /bin/ls .
void test1()
{
	struct s_cmd cmd = {
		.cmd = (char *[]){ "/bin/ls", "." , NULL },
		.env = NULL,
	};

	printf("$?=%d\n", exec(&cmd));
}

// /bin/cat file | /bin/wc -l > filex
void test2()
{

	struct s_cmd cat = {
		.cmd = (char *[]){ "/bin/cat", "Makefile" , NULL },
		.env = NULL,
	};

	struct s_cmd wc = {
		.cmd = (char *[]){ "/usr/bin/wc", "-l" , NULL },
		.env = NULL,
		.outfile = "filex",
	};


	cat.next = &wc;
	wc.prev = &cat;

	printf("$?=%d\n", exec(&cat));
}

// /bin/cat file | /bin/wc -l < filex
void test3()
{
	struct s_cmd cmd = {
		.cmd = (char *[]){ "/bin/ls", "Makefile" , NULL },
		.env = NULL,
	};

	printf("$?=%d\n", exec(&cmd));
}

int main()
{
	// test1();
	test2();
	// test3();
	return 0;
}
