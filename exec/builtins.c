/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:34:32 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/17 11:22:25 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	builtin_echo(struct s_list_cmd *cmd)
{
	int		new_line;
	char	**argv;

	new_line = 1;
	argv = &cmd->cmds_args[1];
	if (*argv && !ft_strcmp(*argv, "-n"))
	{
		new_line = 0;
		argv++;
	}
	while (*argv)
	{
		ft_putstr_fd(*argv++, 1);
		if (*argv)
			ft_putchar_fd(' ', 1);
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}

static int	builtin_cd(struct s_list_cmd *cmd)
{
	char	*path;

	path = cmd->cmds_args[1];
	if (!path)
	{
		path = get_env("HOME");
		if (!path)
			return (__pr_error("cd", NULL, "HOME not set", 1));
	}
	if (chdir(path) < 0)
		return (pr_error("cd", path, 1));
	return (0);
}

static int	builtin_pwd(struct s_list_cmd *cmd)
{
	char	*pwd;

	(void)cmd;
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	return (0);
}

static int	builtin_export(struct s_list_cmd *cmd)
{
	char	**name_values;

	if (arr_size(cmd->cmds_args) < 2)
		return (0);

	name_values = &cmd->cmds_args[1];
	while (*name_values)
	{
		if (set_env(*name_values) < 0)
			return (__pr_error("export", *name_values,
					"not a valid identifier", 1));
		name_values++;
	}
	return (0);
}

static int	builtin_unset(struct s_list_cmd *cmd)
{
	char	**vars;

	vars = &cmd->cmds_args[1];
	if (!*vars)
		return (0);
	while (*vars)
	{
		if (unset_env(*vars) < 0)
			return (__pr_error("unset", *vars, "not a valid identifier", 1));
		vars++;
	}
	return (0);
}

static int	builtin_env(struct s_list_cmd *cmd)
{
	(void)cmd;
	print_env();
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
		exit(0);
	code = ft_atoi_err(cmd->cmds_args[1], &error);
	if (!error)
	{
		if (len > 1)
			return (__pr_error("exit", NULL, "too many arguments", 1));
		exit(code);
	}
	else
	{
		exit(__pr_error("exit", cmd->cmds_args[1], "numeric argument required", 255));
	}
}

builtin_t	get_builtin(char *cmd)
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
