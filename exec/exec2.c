/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:08:02 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/19 20:48:39 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

int	give_birth(struct s_list_cmd *cmd)
{
	int	ret;

	ret = fork();
	if (ret < 0)
		return (pr_error("fork", NULL, -1));
	if (ret > 0)
	{
		cmd->__pid = ret;
		cmd->__is_created = 1;
	}
	return (ret);
}
