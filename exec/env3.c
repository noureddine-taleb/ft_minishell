/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:13:31 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/20 17:46:57 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	__print_env(void)
{
	char	**env;
	char	*name;
	char	*value;

	env = g_state.env;
	while (*env)
	{
		value = ft_strchr(*env, '=') + 1;
		value[-1] = 0;
		name = *env;
		printf("declare -x %s=\"%s\"\n", name, value);
		value[-1] = '=';
		env++;
	}
}

void	__print_local(void)
{
	char	**local;

	local = g_state.local;
	if (!local)
		return ;
	while (*local)
	{
		printf("declare -x %s\n", *local);
		local++;
	}
}

void	print_env(int export_mode)
{
	char	**env;

	env = g_state.env;
	if (!export_mode)
	{
		while (*env)
			printf("%s\n", *env++);
	}
	else
	{
		__print_env();
		__print_local();
	}
}
