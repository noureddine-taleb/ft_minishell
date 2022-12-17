/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:51:32 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/16 19:11:31 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>
#include <stdio.h>

void	init_prev(struct s_list_cmd *cmd)
{
	struct s_list_cmd	*prev;

	prev = NULL;
	while (cmd)
	{
		cmd->prev = prev;
		prev = cmd;
		cmd = cmd->next;
	}
}

int	count_processes(struct s_list_cmd *cmd)
{
	int	count;

	count = 0;
	// printf("counting process count\n");
	while (cmd)
	{
		// printf("cmd = %s\n", cmd->cmds_args[0]);
		cmd = cmd->next;
		count++;
	}
	return (count);
}

int	__pr_error(char *cmd, char *arg, char *msg, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	return (ret);
}

int	pr_error(char *cmd, char *arg, int ret)
{
	__pr_error(cmd, arg, NULL, ret);
	perror(NULL);
	return (ret);
}

void	fatal(char *msg, int status)
{
	exit(pr_error(msg, NULL, status));
}

int	get_append_flag(struct s_list_io_stream *io)
{
	if (io->flags == TOKEN_FILE_APPAND)
		return (O_APPEND);
	else
		return (O_TRUNC);
}

int	arr_size(char **arr)
{
	int	len;

	len = 0;
	while (*arr)
	{
		len++;
		arr++;
	}
	return (len);
}
