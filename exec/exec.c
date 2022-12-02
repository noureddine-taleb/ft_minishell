/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:08:23 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/02 18:56:20 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

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

int	count_processes(struct s_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		cmd = cmd->next;
		count++;
	}
	return (count);
}

int	init_pipes(int count, int pipes[][2])
{
	int	i;
	int	ret;

	i = 0;
	while (count--)
	{
		ret = pipe(pipes[i]);
		if (ret < 0)
			return (ret);
		i++;
	}
	return (0);
}

int	get_append_flag(struct s_cmd *cmd)
{
	if (cmd->append)
		return (O_APPEND);
	else
		return (0);
}

void	die(char *msg)
{
	perror(msg);
	exit(1);
}

void	get_pipe(int pipes[][2], int pipe[2])
{
	static int	i;

	if (i == 0)
	{
		pipe[0] = -1;
		pipe[1] = pipes[i / 2][!(i % 2)];
		i++;
	}
	else
	{
		pipe[0] = pipes[i / 2][!(i % 2)];
		i++;
		pipe[1] = pipes[i / 2][!(i % 2)];
		i++;
	}
}

void	close_unused_pipes(int pipe[2], int pipes[][2], int len)
{
	int	i;

	i = 0;
	while (len)
	{
		if (pipes[i][0] != pipe[0] && pipes[i][0] != pipe[1])
			close(pipes[i][0]);
		if (pipes[i][1] != pipe[0] && pipes[i][1] != pipe[1])
			close(pipes[i][1]);
		len--;
		i++;
	}
}

int	create_child(struct s_cmd *cmd, int pipe[2], int pipes[][2], int len)
{
	int		ret;
	int		outfile;
	int		infile;
	char 	buf[255];

	ret = fork();
	if (ret > 0)
		return (0);
	if (ret < 0)
		return (ret);
	if (cmd->next)
		dup2(pipe[1], STDOUT_FILENO);
	if (cmd->prev)
		dup2(pipe[0], STDIN_FILENO);
	close_unused_pipes(pipe, pipes, len);
	if (cmd->outfile)
	{
		outfile = open(cmd->outfile, O_CREAT | O_WRONLY | get_append_flag(cmd), S_IRUSR | S_IWUSR | S_IRGRP);
		// TODO: sprintf maybe is not allowed + memory leaks
		if (outfile < 0)
		{
			sprintf(buf, "minishell: %s:", cmd->outfile);
			die(buf);
		}
		dup2(outfile, STDOUT_FILENO);
	}
	if (cmd->infile)
	{
		infile = open(cmd->infile, O_RDONLY);
		// TODO: sprintf maybe is not allowed + memory leaks
		if (infile < 0)
		{
			sprintf(buf, "minishell: %s:", cmd->infile);
			die(buf);
		}
		dup2(infile, STDIN_FILENO);
	}

	execve(cmd->cmd[0], cmd->cmd, cmd->env);
	return (0);
}

int	create_children(struct s_cmd *cmd, int pipe_count, int pipes[][2])
{
	int	i;
	int	pipe[2];

	i = 0;
	while (cmd)
	{
		get_pipe(pipes, pipe);
		create_child(cmd, pipe, pipes, pipe_count);
		cmd = cmd->next;
		i++;
	}
	close_unused_pipes((int[2]){-1,-1}, pipes, pipe_count);
	return (0);
}

// TODO: find the correct status code
int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

// TODO: free pipes
int	exec(struct s_cmd *cmd)
{
	int	ret;
	int	exit_status;
	int	status;
	int	process_count;
	int	(*pipes)[2];

	process_count = count_processes(cmd);
	pipes = malloc((process_count - 1) * sizeof (int [2]));
	init_pipes(process_count - 1, pipes);
	create_children(cmd, process_count - 1, pipes);
	// while (process_count--)
	// 	wait(&status);
	return (get_exit_code(status));
}
