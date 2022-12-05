/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:08:23 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/05 18:07:01 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void print_info(char *process)
{
	pid_t pid;

	pid = getpid();
	printf("%s: pid=%d pgid=%d sid=%d\n", process, pid, getpgid(pid), getsid(pid));
}

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

void	init_pipes(int count, int pipes[][2])
{
	int	i;
	int	ret;

	i = 0;
	while (count--)
	{
		ret = pipe(pipes[i]);
		if (ret < 0)
			die("init_pipes", 1);
		i++;
	}
}

int	get_append_flag(struct s_cmd *cmd)
{
	if (cmd->append)
		return (O_APPEND);
	else
		return (0);
}

void	die(char *msg, int status)
{
	perror(msg);
	exit(status);
}

void	get_pipe(int pipes[][2], int pipe[2], int *i)
{
	if ((*i) == 0)
	{
		pipe[0] = -1;
		pipe[1] = pipes[(*i) / 2][!((*i) % 2)];
		(*i)++;
	}
	else
	{
		pipe[0] = pipes[(*i) / 2][!((*i) % 2)];
		(*i)++;
		pipe[1] = pipes[(*i) / 2][!((*i) % 2)];
		(*i)++;
	}
}

void	close_unused_pipes(int pipe[2], int pipes[][2], int len)
{
	int	i;

	i = 0;
	while (len)
	{
		if (pipes[i][0] != pipe[0] && pipes[i][0] != pipe[1])
			if (close(pipes[i][0]))
				die("close_unused_pipes(close)", 4);
		if (pipes[i][1] != pipe[0] && pipes[i][1] != pipe[1])
			if (close(pipes[i][1]))
				die("close_unused_pipes(close)", 4);
		len--;
		i++;
	}
}

int	create_child(struct s_cmd *cmd, int _pipe[2], int pipes[][2], int len)
{
	int		ret;
	int		outfile;
	int		infile;
	char 	buf[255];

	ret = fork();
	if (ret < 0)
			die("create_child(fork)", 2);
	if (ret > 0) {
		cmd->__pid = ret;
		return (0);
	}
	print_info(cmd->cmd[0]);
	if (cmd->next)
		if (dup2(_pipe[1], STDOUT_FILENO) < 0)
			die("create_child(dup2 outpipe)", 3);
	if (cmd->prev)
		if (dup2(_pipe[0], STDIN_FILENO) < 0)
			die("create_child(dup2 inpipe)", 3);
	close_unused_pipes(_pipe, pipes, len);
	if (cmd->outfile)
	{
		outfile = open(cmd->outfile, O_CREAT | O_WRONLY | get_append_flag(cmd), S_IRUSR | S_IWUSR | S_IRGRP);
		// TODO: sprintf maybe is not allowed + memory leaks
		if (outfile < 0)
		{
			sprintf(buf, "minishell: %s", cmd->outfile);
			die(buf, 5);
		}
		if (dup2(outfile, STDOUT_FILENO) < 0)
			die("create_child(dup2 outfile)", 6);
	}
	if (cmd->input == INPUT_FILE)
	{
		infile = open(cmd->infile, O_RDONLY);
		// TODO: sprintf maybe is not allowed + memory leaks
		if (infile < 0)
		{
			sprintf(buf, "minishell: %s", cmd->infile);
			die(buf, 5);
		}
		if (dup2(infile, STDIN_FILENO) < 0)
			die("create_child(dup2 infile)", 6);
	} else if (cmd->input == INPUT_HEREDOC) {
		int local_pipe[2];
		pipe(local_pipe);
		int ret = fork();
		if (ret < 0)
			die("create_child(fork heredoc)", 2);
		else if (ret > 0)
		{
			close(local_pipe[1]);
			if (dup2(local_pipe[0], STDIN_FILENO) < 0)
				die("create_child(dup2 heredoc)", 6);
		}
		else
		{
			close(local_pipe[0]);
			if (dup2(local_pipe[1], STDOUT_FILENO) < 0)
				die("create_child(dup2 heredoc)", 6);
			write(1, cmd->heredoc, strlen(cmd->heredoc));
			exit(0);
		}
	}

	execve(cmd->cmd[0], cmd->cmd, cmd->env);
	die("create_child(execve)", 7);
	return (0);
}

int	create_children(struct s_cmd *cmd, int pipe_count, int pipes[][2])
{
	int	i;
	int	pipe_i;
	int	pipe[2];

	i = 0;
	pipe_i = 0;
	print_info("minishell");
	while (cmd)
	{
		get_pipe(pipes, pipe, &pipe_i);
		create_child(cmd, pipe, pipes, pipe_count);
		cmd = cmd->next;
		i++;
	}
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

void ignore(int signal)
{
	printf("ignoring %d\n", signal);
}
// TODO: free pipes
int	exec(struct s_cmd *cmd)
{
	int	status;
	int	process_count;
	int	pipe_count;
	int	(*pipes)[2];

	signal(SIGINT, ignore);
	process_count = count_processes(cmd);
	pipe_count = process_count - 1;
	pipes = malloc(pipe_count * sizeof (int [2]));
	init_pipes(pipe_count, pipes);
	create_children(cmd, pipe_count, pipes);
	close_unused_pipes((int[2]){-1,-1}, pipes, pipe_count);
	while (cmd) {
		if (waitpid(cmd->__pid, &status, 0) < 0)
			die("exec(wait)", 8);
		cmd = cmd->next;
	}
	return (get_exit_code(status));
}
