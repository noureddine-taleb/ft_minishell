/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:11:00 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/08 19:20:29 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

# define INPUT_HEREDOC 1
# define INPUT_FILE 2

struct s_cmd
{
	char			**cmd;
	char			**env;
	char			*outfile;
	int				append;
	int				input;
// union {
	char			*infile;
	char			*heredoc;
// }
	struct s_cmd	*next;
	struct s_cmd	*prev;

	pid_t			__pid;
};

void	die(char *msg, int status) __dead2;
int		count_processes(struct s_cmd *cmd);
int		get_append_flag(struct s_cmd *cmd);

void	handle_signals(void);

char	*get_env(char *name);

void	init_pipes(int count, int pipes[][2]);
void	get_pipe(int pipes[][2], int pipe[2], int *i);
void	close_unused_pipes(int pipe[2], int pipes[][2], int len);

char	*find_exec(char *exec);

void	handle_pipe(struct s_cmd *cmd, int pipe[2], int pipes[][2], int len);
void	handle_output(struct s_cmd *cmd);
void	handle_input(struct s_cmd *cmd);

int		create_child(struct s_cmd *cmd, int _pipe[2], int pipes[][2], int len);
int		create_children(struct s_cmd *cmd, int pipe_count, int pipes[][2]);
int		get_exit_code(int status);
int		wait_children(struct s_cmd *cmd);
int		exec(struct s_cmd *cmd);

#endif // MINISHELL_H
