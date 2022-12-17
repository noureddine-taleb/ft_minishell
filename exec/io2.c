/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:40:01 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/17 13:40:11 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_stdin_stdout(struct s_list_cmd *cmd)
{
	cmd->__builtin_stdin = dup(STDIN_FILENO);
	if (cmd->__builtin_stdin < 0)
		fatal("dup(save_stdin_stdout)", 1);
	cmd->__builtin_stdout = dup(STDOUT_FILENO);
	if (cmd->__builtin_stdout < 0)
		fatal("dup(save_stdin_stdout)", 1);
}

void	restore_stdin_stdout(struct s_list_cmd *cmd)
{
	if (dup2(cmd->__builtin_stdin, STDIN_FILENO) < 0)
		fatal("dup2(restore_stdin_stdout)", 1);
	if (dup2(cmd->__builtin_stdout, STDOUT_FILENO) < 0)
		fatal("dup2(restore_stdin_stdout)", 1);
	close(cmd->__builtin_stdin);
	close(cmd->__builtin_stdout);
}
