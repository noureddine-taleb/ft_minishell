/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:08:02 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/20 10:48:08 by ntaleb           ###   ########.fr       */
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

void	init_cmd_attr(struct s_list_cmd *cmd)
{
	cmd->__builtin = get_builtin(cmd->cmds_args[0]);
	cmd->__in_subshell = !(cmd->__builtin && !cmd->next && !cmd->prev);
}

int	init_cmd_fd(struct s_list_cmd *cmd, int pipe[2],
			int pipes[][2], int len)
{
	int	ret;

	save_stdin_stdout(cmd);
	handle_pipe(cmd, pipe, pipes, len);
	ret = handle_io(cmd);
	return (ret);
}
