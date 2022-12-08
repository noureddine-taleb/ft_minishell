/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:51:32 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/08 19:18:15 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>

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

void	die(char *msg, int status)
{
	perror(msg);
	exit(status);
}

int	get_append_flag(struct s_cmd *cmd)
{
	if (cmd->append)
		return (O_APPEND);
	else
		return (0);
}
