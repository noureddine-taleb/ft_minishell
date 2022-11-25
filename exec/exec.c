/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:08:23 by ntaleb            #+#    #+#             */
/*   Updated: 2022/11/25 12:21:48 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>

int	exec(struct s_cmd *cmd)
{
	int	ret;
	int	exit_status;
	int	status;

	ret = fork();
	if (ret == 0)
	{
		execve(cmd->cmd[0], cmd->cmd, cmd->env);
	}
	else
	{
		wait(&status);
		printf("$?=");
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			exit_status = WTERMSIG(status) + 128;

		printf("%d", exit_status);
		return (exit_status);
	}
	return (0);
}