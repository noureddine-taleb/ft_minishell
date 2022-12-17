/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:58:22 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/17 10:55:34 by ntaleb           ###   ########.fr       */
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
			return env;
		env++;
	}
	return (NULL);
}

/**
 * if (env_doesnt_exist)
 * 	alloc_new_env_with_extra_slot && free_old_env_if_applicable
 * else
 * 	if (old_spot_can_hold_new_value)
 * 		overwrite_old_value
 * else
 * 	allocate_new_spot && free_old_one_if_applicable
*/
void	__set_env(char *name, char *value)
{
	char	*old_value;
	char	**new_env;

	old_value = get_env(name);
	if (!old_value)
	{
		new_env = malloc((arr_size(g_state.env) + 2) * sizeof (char **));
		ft_memcpy(new_env, g_state.env, arr_size(g_state.env) * sizeof (char **));
		new_env[arr_size(g_state.env)] = init_env_entry(name, value);
		new_env[arr_size(g_state.env) + 1] = NULL;
		if (g_state.env_allocated)
			free(g_state.env);
		g_state.env = new_env;
		g_state.env_allocated = 1;
		return ;
	}
	if (ft_strlen(value) <= ft_strlen(old_value))
	{
		ft_strlcpy(old_value, value, ft_strlen(old_value));
		old_value[ft_strlen(value)] = 0;
		return ;
	}
	old_value -= ft_strlen(name) + 1;
	*get_entry_location(old_value) = init_env_entry(name, value);
	// TODO: old value is leaked
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
		return (-1);
	*value = 0;
	value++;
	name = name_value;
	ret = -1;
	if (valid_env_name(name))
	{
		__set_env(name, value);
		ret = 0;
	}
	return (value[-1] = '=', ret);
}

int	unset_env(char *name)
{
	char	*value;
	char	**env;

	env = g_state.env;
	if (!valid_env_name(name))
		return (-1);
	value = get_env(name);
	if (!value)
		return (0);
	value -= ft_strlen(name) + 1;
	env = get_entry_location(value);
	// TODO: this may not work
	// free(*env);
	ft_memmove(env, env + 1, (arr_size(env + 1) + 1) * sizeof (char **));
	return (1);
}

void	print_env(void)
{
	char	**env;

	env = g_state.env;
	while (*env)
		printf("%s\n", *env++);
}

/**
 * result need not be freed
*/
char	*get_env(char *name)
{
	char	**_env;
	char	*value;

	_env = g_state.env;
	value = NULL;
	name = ft_strjoin(name, "=");
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
