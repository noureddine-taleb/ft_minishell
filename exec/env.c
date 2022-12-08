/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:58:22 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/08 18:59:33 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env;

char	*get_env(char *name)
{
	char	**_env;
	char	*value;

	_env = env;
	value = NULL;
	name = ft_strjoin(name, "=");
	if (!name)
		die("out of memory", 9);
	while (*_env)
	{
		if (!ft_strncmp(*_env, name, ft_strlen(name)))
		{
			value = ft_strchr(*_env, '=') + 1;
			break ;
		}
		_env++;
	}
	free(name);
	return (value);
}
