/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:02:47 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/08 19:18:35 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	handle_pipe(struct s_cmd *cmd, int pipe[2], int pipes[][2], int len)
{
	if (cmd->next)
		if (dup2(pipe[1], STDOUT_FILENO) < 0)
			die("create_child(dup2 outpipe)", 3);
	if (cmd->prev)
		if (dup2(pipe[0], STDIN_FILENO) < 0)
			die("create_child(dup2 inpipe)", 3);
	close_unused_pipes(pipe, pipes, len);
}

void	handle_output(struct s_cmd *cmd)
{
	int		outfile;

	if (!cmd->outfile)
		return ;
	outfile = open(cmd->outfile, O_CREAT | O_WRONLY | get_append_flag(cmd),
			S_IRUSR | S_IWUSR | S_IRGRP);
	if (outfile < 0)
		die(cmd->outfile, 5);
	if (dup2(outfile, STDOUT_FILENO) < 0)
		die("create_child(dup2 outfile)", 6);
}

static void	__handle_input_file(struct s_cmd *cmd)
{
	int	infile;

	infile = open(cmd->infile, O_RDONLY);
	if (infile < 0)
		die(cmd->infile, 5);
	if (dup2(infile, STDIN_FILENO) < 0)
		die("create_child(dup2 infile)", 6);
}

static void	__handle_input_heredoc(struct s_cmd *cmd)
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
		write(STDOUT_FILENO, cmd->heredoc, ft_strlen(cmd->heredoc));
		exit(0);
	}
}

void	handle_input(struct s_cmd *cmd)
{
	if (cmd->input == INPUT_FILE)
		__handle_input_file(cmd);
	else if (cmd->input == INPUT_HEREDOC)
		__handle_input_heredoc(cmd);
}
