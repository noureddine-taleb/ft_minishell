/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:40:57 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/20 13:45:59 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	builtin_env(struct s_list_cmd *cmd)
{
	(void)cmd;
	print_env(0);
	return (0);
}

/**
 * print "exit\n"
 * 
 * if argc == 0
 * 	exit(0)
 * 
 * if argv[0] is number
 * 	if (argc > 1)
 * 		bailout("exit: too many arguments", 1)
 * else
 * 	perror("exit: {argv[0]}: numeric argument required"), exit(255)
*/
static int	builtin_exit(struct s_list_cmd *cmd)
{
	int	len;
	int	error;
	int	code;

	error = 0;
	ft_putstr_fd("exit\n", 1);
	len = arr_size(cmd->cmds_args) - 1;
	if (len == 0)
		exit(g_state.exit_status);
	code = ft_atoi_err(cmd->cmds_args[1], &error);
	if (!error)
	{
		if (len > 1)
			return (__pr_error("exit", NULL, "too many arguments", -1));
		exit(code);
	}
	else
	{
		exit(__pr_error("exit", cmd->cmds_args[1],
				"numeric argument required", 255));
	}
}

int	builtin_echo(struct s_list_cmd *cmd);
int	builtin_cd(struct s_list_cmd *cmd);
int	builtin_pwd(struct s_list_cmd *cmd);
int	builtin_export(struct s_list_cmd *cmd);
int	builtin_unset(struct s_list_cmd *cmd);
int	builtin_env(struct s_list_cmd *cmd);
int	builtin_exit(struct s_list_cmd *cmd);

t_builtin	get_builtin(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (!ft_strcmp(cmd, "echo"))
		return (builtin_echo);
	if (!ft_strcmp(cmd, "cd"))
		return (builtin_cd);
	if (!ft_strcmp(cmd, "pwd"))
		return (builtin_pwd);
	if (!ft_strcmp(cmd, "export"))
		return (builtin_export);
	if (!ft_strcmp(cmd, "unset"))
		return (builtin_unset);
	if (!ft_strcmp(cmd, "env"))
		return (builtin_env);
	if (!ft_strcmp(cmd, "exit"))
		return (builtin_exit);
	return (NULL);
}
