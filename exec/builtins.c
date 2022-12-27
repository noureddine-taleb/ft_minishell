/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:34:32 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/21 08:45:26 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_echo(struct s_list_cmd *cmd)
{
	int		new_line;
	char	**argv;

	new_line = 1;
	argv = &cmd->cmds_args[1];
	while (*argv && arg_equal_flag(*argv, 'n'))
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

int	builtin_cd(struct s_list_cmd *cmd)
{
	char		*path;

	path = cmd->cmds_args[1];
	if (!path)
	{
		path = get_env("HOME");
		if (!path)
			return (__pr_error("cd", NULL, "HOME not set", 1));
	}
	else if (!ft_strcmp(path, "-"))
	{
		path = get_env("OLDPWD");
		if (!path)
			return (__pr_error("cd", NULL, "OLDPWD not set", 1));
	}
	if (chdir(path) < 0)
		return (pr_error("cd", path, -1));
	else
	{
		path = getcwd(NULL, 0);
		__set_env("OLDPWD", get_env("PWD"));
		__set_env("PWD", path);
		free(path);
		return (0);
	}
}

int	builtin_pwd(struct s_list_cmd *cmd)
{
	(void)cmd;
	printf("%s\n", get_env("PWD"));
	return (0);
}

int	builtin_export(struct s_list_cmd *cmd)
{
	char	**name_values;
	int		ret;

	if (arr_size(cmd->cmds_args) == 1)
	{
		print_env(1);
		return (0);
	}
	name_values = &cmd->cmds_args[1];
	ret = 0;
	while (*name_values)
	{
		if (set_env(*name_values) < 0)
			ret = __pr_error("export", *name_values,
					"not a valid identifier", -1);
		name_values++;
	}
	return (ret);
}

int	builtin_unset(struct s_list_cmd *cmd)
{
	char	**vars;
	int		ret;

	vars = &cmd->cmds_args[1];
	if (!*vars)
		return (0);
	ret = 0;
	while (*vars)
	{
		if (unset_env(*vars) < 0)
			ret = __pr_error("unset", *vars, "not a valid identifier", -1);
		vars++;
	}
	return (ret);
}
