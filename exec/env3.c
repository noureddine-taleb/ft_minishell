/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:13:31 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/20 12:14:01 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(int export_mode)
{
	char	**env;
	char	*name;
	char	*value;

	env = g_state.env;
	if (!export_mode)
	{		
		while (*env)
			printf("%s\n", *env++);
	}
	else
	{
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
}
