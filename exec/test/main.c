#include "../minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char **env;
// ls .
void test1()
{
	struct s_cmd cmd = {
		.cmd = (char *[]){ "ls", "." , NULL },
	};

	printf("ls .\n");
	printf("$?=%d\n", exec(&cmd));
}

// /bin/cat Makefile | /bin/wc -l
void test2()
{
	struct s_cmd cat = {
		.cmd = (char *[]){ "/bin/cat", "Makefile" , NULL },
	};

	struct s_cmd wc = {
		.cmd = (char *[]){ "/usr/bin/wc", "-l" , NULL },
	};

	cat.next = &wc;
	wc.prev = &cat;

	printf("/bin/cat Makefile | /bin/wc -l\n");
	printf("$?=%d\n", exec(&cat));
}

// /bin/cat Makefile | /bin/wc -l < main.c
void test3()
{
	struct s_cmd cat = {
		.cmd = (char *[]){ "/bin/cat", "Makefile" , NULL },
	};

	struct s_cmd wc = {
		.cmd = (char *[]){ "/usr/bin/wc", "-l" , NULL },
		.input = INPUT_FILE,
		.infile = "main.c",
	};

	cat.next = &wc;
	wc.prev = &cat;

	printf("/bin/cat Makefile | /bin/wc -l < main.c\n");
	printf("$?=%d\n", exec(&cat));
}

// /bin/cat Makefile | /bin/wc -l > filex
void test4()
{
	struct s_cmd cat = {
		.cmd = (char *[]){ "/bin/cat", "Makefile" , NULL },
	};

	struct s_cmd wc = {
		.cmd = (char *[]){ "/usr/bin/wc", "-l" , NULL },
		.outfile = "filex",
	};


	cat.next = &wc;
	wc.prev = &cat;

	printf("/bin/cat Makefile | /bin/wc -l > filex\n");
	printf("$?=%d\n", exec(&cat));
}

// /bin/cat | /bin/wc -l # test signal exit code
void test5()
{
	struct s_cmd cat = {
		.cmd = (char *[]){ "/bin/cat", NULL },
	};

	struct s_cmd wc = {
		.cmd = (char *[]){ "/usr/bin/wc", "-l" , NULL },
	};

	cat.next = &wc;
	wc.prev = &cat;

	printf("/bin/cat | /bin/wc -l\n");
	printf("$?=%d\n", exec(&cat));
}

// ./cat1 | ./cat2 # test that cat2 exit status is what is reported
void test6()
{
	struct s_cmd cat1 = {
		.cmd = (char *[]){ "./cat1", NULL },
	};


	struct s_cmd cat2 = {
		.cmd = (char *[]){ "./cat2", NULL },
	};

	cat1.next = &cat2;
	cat2.prev = &cat1;

	printf("./cat1 | ./cat2\n");
	printf("$?=%d\n", exec(&cat1));
}

// wc -l <<EOF
// hello world
// EOF # test that cat2 exit status is what is reported
void test7()
{
	struct s_cmd wc = {
		.cmd = (char *[]){ "/usr/bin/wc", NULL },
		.input = INPUT_HEREDOC,
		.heredoc = "hello world!\n",
	};


	printf("wc -l <<EOF\n");
	printf("$?=%d\n", exec(&wc));
}

// hello (local binary with no path var)
void test8()
{
	struct s_cmd cmd = {
		.cmd = (char *[]){ "hello", NULL },
	};

	printf("hello\n");
	printf("$?=%d\n", exec(&cmd));
}

int main(int argc, char **argv, char **envp)
{
	env = envp;
	argc--;
	argv++;
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp("1", *argv))
			test1();
		if (!strcmp("2", *argv))
			test2();
		if (!strcmp("3", *argv))
			test3();
		if (!strcmp("4", *argv))
			test4();
		if (!strcmp("5", *argv))
			test5();
		if (!strcmp("6", *argv))
			test6();
		if (!strcmp("7", *argv))
			test7();
		if (!strcmp("8", *argv))
			test8();
		argv++;
	}
	return 0;
}
