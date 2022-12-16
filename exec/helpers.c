/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:51:32 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/27 11:55:19 by ntaleb           ###   ########.fr       */
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

int		pr_error(char *msg, int ret)
{
	char	*toprint;

	toprint = ft_strjoin("minishell: ", msg);
	perror(toprint);
	free(toprint);
	return (ret);
}

void	die(char *msg, int status)
{
	pr_error(msg, status);
	exit(status);
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
