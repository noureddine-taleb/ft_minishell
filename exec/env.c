/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:58:22 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/20 17:38:41 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*init_env_entry(char *name, char *value);

/**
 * if (env_doesnt_exist)
 * 	alloc_new_env_with_extra_slot && free_old_env
 * else
 * 	if (old_spot_can_hold_new_value)
 * 		overwrite_old_value
 * else
 * 	allocate_new_entry && free_old_one
*/
void	__set_env(char *name, char *value)
{
	char	*old_value;
	char	**new_env;
	char	**new_value;

	old_value = get_env(name);
	if (!old_value)
	{
		new_env = ft_calloc((arr_size(g_state.env) + 2), sizeof (char **));
		ft_memcpy(new_env, g_state.env,
			arr_size(g_state.env) * sizeof (char **));
		new_env[arr_size(g_state.env)] = init_env_entry(name, value);
		free(g_state.env);
		g_state.env = new_env;
		__unset_local(name);
		return ;
	}
	if (ft_strlen(value) <= ft_strlen(old_value))
	{
		ft_strlcpy(old_value, value, ft_strlen(old_value) + 1);
		return ;
	}
	old_value -= ft_strlen(name) + 1;
	new_value = get_entry_location(old_value, g_state.env);
	free(*new_value);
	*new_value = init_env_entry(name, value);
}

/**
 * parse and sanity check name_value:
 * name_value includes =
 * name is valid env string
*/
int	set_env(char *name_value)
{
	char	*name;
	char	*value;
	int		ret;

	value = ft_strchr(name_value, '=');
	if (!value)
	{
		if (valid_env_name(name_value))
			return (__set_local(name_value), 0);
		return (-1);
	}
	*value = 0;
	value++;
	name = name_value;
	ret = -1;
	if (valid_env_name(name))
	{
		__set_env(name, value);
		__unset_local(name);
		ret = 0;
	}
	return (value[-1] = '=', ret);
}

int	__unset_env(char *name)
{
	char	*value;
	char	**env;

	value = get_env(name);
	if (!value)
		return (0);
	value -= ft_strlen(name) + 1;
	env = get_entry_location(value, g_state.env);
	free(*env);
	ft_memmove(env, env + 1, (arr_size(env)) * sizeof (char **));
	return (1);
}

int	unset_env(char *name)
{
	if (!valid_env_name(name))
		return (-1);
	return (__unset_local(name), __unset_env(name));
}

/**
 * result should not be freed
*/
char	*get_env(char *name)
{
	char	**env;
	char	*value;

	env = g_state.env;
	value = NULL;
	name = ft_strjoin(name, "=");
	while (*env)
	{
		if (!ft_strncmp(*env, name, ft_strlen(name)))
		{
			value = ft_strchr(*env, '=') + 1;
			break ;
		}
		env++;
	}
	free(name);
	return (value);
}
