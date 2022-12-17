/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:08:23 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/17 16:00:12 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	give_birth(struct s_list_cmd *cmd);

/**
 * steps:
 * parent: create all pipes
 * parent: fork the childrens
 * child: handle pipes
 * child: save old fds
 * child: handle io
 * child: close unused pipes
 * child: exec the program
 * parent: close all pipes
 * parent: wait for children
*/
int	execute_cmd(struct s_list_cmd *cmd)
{
	int		ret;
	char	*full_path;

	if (cmd->__builtin)
		return (cmd->__builtin(cmd));
	ret = find_exec(cmd->cmds_args[0], &full_path);
	if (ret < 0)
		return (-ret);
	free(cmd->cmds_args[0]);
	cmd->cmds_args[0] = full_path;
	if (execve(cmd->cmds_args[0], cmd->cmds_args, g_state.env) < 0)
		fatal(cmd->cmds_args[0], 1);
	return (0);
}

int	create_child(struct s_list_cmd *cmd, int _pipe[2], int pipes[][2], int len)
{
	int	ret;

	cmd->__builtin = get_builtin(cmd->cmds_args[0]);
	cmd->__in_subshell = !(cmd->__builtin && !cmd->next && !cmd->prev);
	if (cmd->__in_subshell && give_birth(cmd))
		return (0);
	save_stdin_stdout(cmd);
	handle_pipe(cmd, _pipe, pipes, len);
	ret = handle_io(cmd);
	if (ret < 0)
	{
		if (cmd->__in_subshell)
			exit(-ret);
		return (restore_stdin_stdout(cmd), cmd->__builtin_exit_status = -ret);
	}
	if (!*cmd->cmds_args)
		exit(0);
	ret = execute_cmd(cmd);
	if (cmd->__in_subshell)
		exit(ret);
	return (restore_stdin_stdout(cmd), cmd->__builtin_exit_status = ret);
}

int	create_children(struct s_list_cmd *cmd, int pipe_count, int pipes[][2])
{
	int	i;
	int	pipe_i;
	int	pipe[2];

	i = 0;
	pipe_i = 0;
	while (cmd)
	{
		get_pipe(pipes, pipe, &pipe_i, pipe_count);
		create_child(cmd, pipe, pipes, pipe_count);
		cmd = cmd->next;
		i++;
	}
	return (0);
}

int	wait_children(struct s_list_cmd *cmd)
{
	int	status;

	while (cmd)
	{
		if (!cmd->__in_subshell)
			status = cmd->__builtin_exit_status;
		else if (waitpid(cmd->__pid, &status, 0) > 0)
			status = get_exit_code(status);
		else
			fatal("wait_children(wait)", 1);
		cmd = cmd->next;
	}
	return (status);
}

int	exec(struct s_list_cmd *cmd)
{
	int	status;
	int	process_count;
	int	pipe_count;
	int	(*pipes)[2];

	init_prev(cmd);
	process_count = count_processes(cmd);
	pipe_count = process_count - 1;
	pipes = malloc(pipe_count * sizeof (int [2]));
	init_pipes(pipe_count, pipes);
	create_children(cmd, pipe_count, pipes);
	close_unused_pipes((int [2]){-1, -1}, pipes, pipe_count);
	free(pipes);
	status = wait_children(cmd);
	return (status);
}
