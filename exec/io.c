/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:02:47 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/13 15:06:14 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

static void	__handle_io_file(struct s_list_cmd *cmd,
				struct s_list_io_stream *io)
{
	int	file;
	int	ret;

	if (io->flags & IO_IN_FILE)
		file = open(io->target, O_RDONLY);
	else if (io->flags & IO_IN_FILE)
		file = open(io->target, O_CREAT | O_WRONLY | get_append_flag(cmd),
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (file < 0)
		die(io->target, 5);
	if (io->flags & IO_IN_FILE)
		ret = dup2(file, STDIN_FILENO);
	else if (io->flags & IO_IN_FILE)
		ret = dup2(file, STDOUT_FILENO);
	if (ret < 0)
		die("create_child(dup2 file)", 6);
}

static void	__handle_heredoc(struct s_list_cmd *cmd,
				struct s_list_io_stream *io)
{
	int	local_pipe[2];
	int	ret;

	pipe(local_pipe);
	ret = fork();
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
		write(STDOUT_FILENO, io->target, ft_strlen(io->target));
		exit(0);
	}
}

void	handle_io(struct s_list_cmd *cmd)
{
	struct s_list_io_stream	*io;

	io = cmd->io;
	while (io)
	{
		if (io->type == TYPE_HEREDOC)
			__handle_heredoc(cmd, io);
		else if (io->type == TYPE_FILE)
			__handle_io_file(cmd, io);
		io = io->next;
	}
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
}
