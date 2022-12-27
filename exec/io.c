/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:02:47 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/19 17:08:00 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_pipe(struct s_list_cmd *cmd, int pipe[2],
			int pipes[][2], int len)
{
	if (cmd->next)
		if (dup2(pipe[1], STDOUT_FILENO) < 0)
			fatal("create_child(dup2 outpipe)", 1);
	if (cmd->prev)
		if (dup2(pipe[0], STDIN_FILENO) < 0)
			fatal("create_child(dup2 inpipe)", 1);
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
		return (pr_error(io->target, NULL, -1));
	if (io->flags == TOKEN_FILE_INP)
		ret = dup2(file, STDIN_FILENO);
	else
		ret = dup2(file, STDOUT_FILENO);
	if (ret < 0)
		fatal("__handle_io_file(dup2)", 1);
	return (0);
}

static void	__handle_heredoc(struct s_list_io_stream *io)
{
	int	local_pipe[2];
	int	ret;

	if (pipe(local_pipe) < 0)
		fatal("__handle_heredoc(pipe)", 1);
	ret = fork();
	if (ret < 0)
		fatal("__handle_heredoc(fork)", 1);
	else if (ret > 0)
	{
		close(local_pipe[1]);
		if (dup2(local_pipe[0], STDIN_FILENO) < 0)
			fatal("__handle_heredoc(dup2)", 1);
	}
	else
	{
		close(local_pipe[0]);
		if (dup2(local_pipe[1], STDOUT_FILENO) < 0)
			fatal("__handle_heredoc(dup2)", 1);
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
		{
			if (__handle_io_file(io) < 0)
				return (-1);
		}
		else if (io->flags == TOKEN_AMBIGUOUS_REDIRECTION)
			return (__pr_error(io->target, NULL, "ambiguous redirect", -1));
		io = io->next;
	}
	return (0);
}
