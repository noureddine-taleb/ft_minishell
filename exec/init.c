/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:15:57 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/20 13:16:23 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_shell(void)
{
	char				*pwd;

	__unset_env("OLDPWD");
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (pr_error("shell-init", "error retrieving current \
directory: getcwd: cannot access parent directories", -1));
	__set_env("PWD", pwd);
	free(pwd);
	return (0);
}

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
