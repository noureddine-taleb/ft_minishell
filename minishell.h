#if !defined(MINISHELL_H)
#define MINISHELL_H

#include <fcntl.h>
struct cmd {
	char **cmd;
	char **env;
	char *outfile;
	int	 outflags;
	char *infile;
	char *herdoc;
	struct cmd *next;
	struct cmd *prev;
};

execve(c.cmd[0], c.cmd);
#endif // MINISHELL_H

