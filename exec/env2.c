/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:02:43 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/17 13:03:35 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	valid_env_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	valid_env_name(char *var)
{
	if (!ft_strlen(var))
		return (0);
	if (ft_isdigit(*var))
		return (0);
	while (*var)
	{
		if (!valid_env_char(*var))
			return (0);
		var++;
	}
	return (1);
}

char	*init_env_entry(char *name, char *value)
{
	char	*slot;
	int		size;

	size = ft_strlen(name) + ft_strlen(value) + 2;
	slot = malloc(size);
	slot[0] = 0;
	ft_strlcat(slot, name, size);
	ft_strlcat(slot, "=", size);
	ft_strlcat(slot, value, size);
	return (slot);
}

char	**get_entry_location(char *addr)
{
	char	**env;

	env = g_state.env;
	while (*env)
	{
		if (*env == addr)
			return (env);
		env++;
	}
	return (NULL);
}
