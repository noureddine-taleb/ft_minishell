/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:08:23 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/16 13:08:27 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/wait.h>
#include <stdio.h>

/**
 * count number of processes in the pipeline
 * create forks accordingly
 * link processes with pipes
 * add in/out files
 * 
 * 
 * steps:
 * parent: create all pipes
 * parent: fork the childrens
 * child: open any stdout or stdin files
 * child: dup2 phase
 * child: execve phase
 * parent: close pipes in the parent
 * parent: wait for the pocess group to exit
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
	if (execve(cmd->cmds_args[0], cmd->cmds_args, g_env) < 0)
		die(cmd->cmds_args[0], 1);
	return (0);
}

int	create_child(struct s_list_cmd *cmd, int _pipe[2], int pipes[][2], int len)
{
	int			ret;

	// printf("root = %p\n", cmd->cmds_args);
	cmd->__builtin = get_builtin(cmd->cmds_args[0]);
	cmd->__in_subshell = (!cmd->__builtin || cmd->next || cmd->prev);
	if (cmd->__in_subshell)
	{
		ret = fork();
		if (ret < 0)
			die("create_child(fork)", 2);
		if (ret > 0)
			return (cmd->__pid = ret, 0);
	}
	else
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

int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
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
			die("wait_children(wait)", 8);
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

	handle_signals();
	init_prev(cmd);
	process_count = count_processes(cmd);
	// printf("process count = %d\n", process_count);
	pipe_count = process_count - 1;
	pipes = malloc(pipe_count * sizeof (int [2]));
	init_pipes(pipe_count, pipes);
	create_children(cmd, pipe_count, pipes);
	close_unused_pipes((int [2]){-1, -1}, pipes, pipe_count);
	free(pipes);
	status = wait_children(cmd);
	// printf("status = %d\n", status);
	return (status);
}
