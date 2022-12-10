/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:58:22 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/10 15:19:52 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env;
int		env_allocated = 0;

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

/**
 * allocate new env with 1 extra slot, if the var doesn't already exists
 * duplicate name_value after checking its validity
 * insert it into the env
 * free the old env
 * change g_env global variable
*/
int	set_env(char *name_value)
{
	/**
	 * do the parsing and sanity checks
	*/
	
	char *name;
	char *value;

	ft_strchr(name_value, '=');
	__set_env(name, value);
}

int	__set_env(char *name, char *value)
{
	char	*old_value;

	old_value = getenv(name);
	if (!old_value)
	{
		// allocated new slot
	}
	else
	{
		// check if the old slot is capable of holding the new value
		// otherwise allocated a new buffer
		
	}
}

int	unset_env(char *name)
{
	char	*value;
	char	**env;

	env = g_env;
	if (!valid_env_name(name))
		return (-1);
	value = get_env(name);
	if (!value)
		return (0);
	value -= ft_strlen(name) + 1;
	while (*env)
	{
		if (*env == value)
			break ;
		env++;
	}
	free(*env);
	ft_memmove(env, env + 1, (arr_size(env + 1) + 1) * sizeof (char **));
	return (1);
}

void	print_env(void)
{
	char	**env;

	env = g_env;
	while (*env)
		ft_printf("%s\n", *env++);
}


/**
 * result need not be freed
 * TODO: to be removed because it is already allowed to use the one from standard library
*/
char	*get_env(char *name)
{
	char	**_env;
	char	*value;

	_env = g_env;
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
