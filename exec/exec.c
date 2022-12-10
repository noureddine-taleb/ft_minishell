/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:08:23 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/10 13:45:38 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

int	create_child(struct s_cmd *cmd, int _pipe[2], int pipes[][2], int len)
{
	int		ret;

	ret = fork();
	if (ret < 0)
		die("create_child(fork)", 2);
	if (ret > 0)
		return (cmd->__pid = ret, 0);
	handle_pipe(cmd, _pipe, pipes, len);
	handle_output(cmd);
	handle_input(cmd);
	cmd->cmd[0] = find_exec(cmd->cmd[0]);
	execve(cmd->cmd[0], cmd->cmd, g_env);
	die("create_child(execve)", 7);
}

int	create_children(struct s_cmd *cmd, int pipe_count, int pipes[][2])
{
	int	i;
	int	pipe_i;
	int	pipe[2];

	i = 0;
	pipe_i = 0;
	while (cmd)
	{
		get_pipe(pipes, pipe, &pipe_i);
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

int	wait_children(struct s_cmd *cmd)
{
	int	status;

	while (cmd)
	{
		if (waitpid(cmd->__pid, &status, 0) < 0)
			die("exec(wait)", 8);
		cmd = cmd->next;
	}
	return (status);
}

int	exec(struct s_cmd *cmd)
{
	int	status;
	int	process_count;
	int	pipe_count;
	int	(*pipes)[2];

	handle_signals();
	process_count = count_processes(cmd);
	pipe_count = process_count - 1;
	pipes = malloc(pipe_count * sizeof (int [2]));
	init_pipes(pipe_count, pipes);
	create_children(cmd, pipe_count, pipes);
	close_unused_pipes((int [2]){-1, -1}, pipes, pipe_count);
	free(pipes);
	status = wait_children(cmd);
	return (get_exit_code(status));
}
