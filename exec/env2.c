/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:02:43 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/20 15:17:06 by ntaleb           ###   ########.fr       */
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

char	**clone_env(char **env)
{
	int		len;
	char	**new_env;
	int		i;
	int		entry_size;

	i = 0;
	len = arr_size(env);
	new_env = ft_calloc(len + 1, sizeof (char **));
	while (i < len)
	{
		entry_size = ft_strlen(env[i]) + 1;
		new_env[i] = malloc(entry_size);
		ft_strlcpy(new_env[i], env[i], entry_size);
		i++;
	}
	return (new_env);
}
