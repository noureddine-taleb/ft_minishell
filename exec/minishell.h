/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:11:00 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/16 10:58:01 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

# define TYPE_FILE 0
# define TYPE_HEREDOC 1

# define IO_OUT_FILE 0
# define IO_IN_FILE 1
# define IO_APPEND 2

struct s_list_cmd;
typedef int (*builtin_t)(struct s_list_cmd *cmd);
struct s_list_io_stream
{
	int						type;
	char					*target;
	int						flags;
	struct s_list_io_stream	*next;
};

typedef struct s_list_cmd
{
	char						**cmds_args;
	struct s_list_io_stream		*io;
	struct s_list_cmd			*next;
	struct s_list_cmd			*prev;

	pid_t						__pid;
	builtin_t					__builtin;
	int							__builtin_exit_status;
	int							__builtin_stdin;
	int							__builtin_stdout;
	int							__in_subshell;
}	t_list_cmd;


extern char **g_env;

int		pr_error(char *msg, int ret);
void	die(char *msg, int status) __dead2;
int		count_processes(struct s_list_cmd *cmd);
int		get_append_flag(struct s_list_io_stream *io);
int		arr_size(char **path);
void	init_prev(struct s_list_cmd *cmd);

void	handle_signals(void);

char	*get_env(char *name);
void	print_env(void);
int		valid_env_name(char *var);
int		unset_env(char *name);
int		set_env(char *name_value);

void	init_pipes(int count, int pipes[][2]);
void	get_pipe(int pipes[][2], int pipe[2], int *i);
void	close_unused_pipes(int pipe[2], int pipes[][2], int len);

builtin_t	get_builtin(char *cmd);
int			find_exec(char *exec, char **full_path);

void	handle_pipe(struct s_list_cmd *cmd,
			int pipe[2], int pipes[][2], int len);
int		handle_io(struct s_list_cmd *cmd);
void	save_stdin_stdout(struct s_list_cmd *cmd);
void	restore_stdin_stdout(struct s_list_cmd *cmd);

int		create_child(struct s_list_cmd *cmd, int _pipe[2],
			int pipes[][2], int len);
int		create_children(struct s_list_cmd *cmd, int pipe_count, int pipes[][2]);
int		get_exit_code(int status);
int		wait_children(struct s_list_cmd *cmd);
int		exec(struct s_list_cmd *cmd);

#endif // MINISHELL_H
