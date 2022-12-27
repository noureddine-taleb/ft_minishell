/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:02:47 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/27 11:53:40 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

void	handle_pipe(struct s_list_cmd *cmd, int pipe[2],
			int pipes[][2], int len)
{
	if (cmd->next)
		if (dup2(pipe[1], STDOUT_FILENO) < 0)
			die("create_child(dup2 outpipe)", 3);
	if (cmd->prev)
		if (dup2(pipe[0], STDIN_FILENO) < 0)
			die("create_child(dup2 inpipe)", 3);
	close_unused_pipes(pipe, pipes, len);
}

static int	__handle_io_file(struct s_list_io_stream *io)
{
	int	file;
	int	ret;

	if (io->flags == TOKEN_FILE_INP)
		file = open(io->target, O_RDONLY);
	else
		file = open(io->target, O_CREAT | O_WRONLY | get_append_flag(io),
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (file < 0)
		return (pr_error(io->target, -1));
	if (io->flags == TOKEN_FILE_INP)
		ret = dup2(file, STDIN_FILENO);
	else
		ret = dup2(file, STDOUT_FILENO);
	if (ret < 0)
		die("__handle_io_file(dup2)", 1);
	return (0);
}

static void	__handle_heredoc(struct s_list_io_stream *io)
{
	int	local_pipe[2];
	int	ret;

	if (pipe(local_pipe) < 0)
		die("__handle_heredoc(pipe)", 1);
	ret = fork();
	if (ret < 0)
		die("__handle_heredoc(fork)", 1);
	else if (ret > 0)
	{
		close(local_pipe[1]);
		if (dup2(local_pipe[0], STDIN_FILENO) < 0)
			die("__handle_heredoc(dup2)", 1);
	}
	else
	{
		close(local_pipe[0]);
		if (dup2(local_pipe[1], STDOUT_FILENO) < 0)
			die("__handle_heredoc(dup2)", 1);
		write(STDOUT_FILENO, io->target, ft_strlen(io->target));
		exit(0);
	}
}

int	handle_io(struct s_list_cmd *cmd)
{
	struct s_list_io_stream	*io;

	io = cmd->io;
	while (io)
	{
		if (io->flags == TOKEN_FILE_HERDOC)
			__handle_heredoc(io);
		else if (io->flags == TOKEN_FILE_APPAND
				|| io->flags == TOKEN_FILE_INP
				|| io->flags == TOKEN_FILE_OUT
				 )
			if (__handle_io_file(io) < 0)
				return (-1);
		io = io->next;
	}
	return (0);
}

void	save_stdin_stdout(struct s_list_cmd *cmd)
{
	cmd->__builtin_stdin = dup(STDIN_FILENO);
	if (cmd->__builtin_stdin < 0)
		die("dup(save_stdin_stdout)", 1);
	cmd->__builtin_stdout = dup(STDOUT_FILENO);
	if (cmd->__builtin_stdout < 0)
		die("dup(save_stdin_stdout)", 1);
}

void	restore_stdin_stdout(struct s_list_cmd *cmd)
{
	if (dup2(cmd->__builtin_stdin, STDIN_FILENO) < 0)
		die("dup2(restore_stdin_stdout)", 1);
	if (dup2(cmd->__builtin_stdout, STDOUT_FILENO) < 0)
		die("dup2(restore_stdin_stdout)", 1);
	close(cmd->__builtin_stdin);
	close(cmd->__builtin_stdout);
}
