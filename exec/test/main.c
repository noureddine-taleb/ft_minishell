#include "../minishell.h"
#include <stdlib.h>

int main()
{
	struct s_cmd cmd = {
		.cmd = (char *[]){ "/bin/ls", "Makefile" , NULL },
		.env = NULL,
	};

	exec(&cmd);
}