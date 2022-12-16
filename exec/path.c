/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:55:05 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/16 11:15:34 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * result should be freed
*/
static char	*combine_path_with_exec(char *path, char *exec)
{
	char	*full_path;

	if (path[ft_strlen(path) - 1] == '/')
		return (ft_strjoin(path, exec));
	path = ft_strjoin(path, "/");
	full_path = ft_strjoin(path, exec);
	free(path);
	return (full_path);
}

static void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

int	check_exec(char	*exec)
{
	if (access(exec, F_OK) < 0)
		return (-ENOENT);
	if (access(exec, X_OK) < 0)
		return (-EACCES);
	return (0);
}

/**
 * this routine looks for the exec following the shell semantics
 * if the exec is found and is executable it returns the success and the full path is stored in `full_path`
 * otherwise it prints an error and returns the error code
 * 
 * if path is empty look for the exec in the current dir
 * otherwise look for the exec in path
 * 
 * if a file exist but not executable skip it
 * but remember the first instance that exists but not executable,
 * this value will be showen in the error message.
 * 
 * TODO: this need a rewrite
*/
int	find_exec(char *exec, char **full_path)
{
	char	**path;
	int		i;
	int		path_len;
	int		ret;
	char	*error;

	path = ft_split(get_env("PATH"), ':');
	path_len = arr_size(path);
	if (ft_strchr(exec, '/') || !path_len)
	{
		if (check_exec(exec) < 0)
			return (pr_error(*full_path, -1));
		return (free_path(path), *full_path = ft_strdup(exec), 0);
	}
	i = 0;
	error = NULL;
	while (path[i])
	{
		*full_path = combine_path_with_exec(path[i], exec);
		if (!access(*full_path, X_OK))
			return (free_path(path), 0);
		else if (!access(*full_path, F_OK) && !error)
			error = *full_path;
		else
			free(*full_path);
		if (access(*full_path, F_OK))
			ret = 127;
		else
			ret = 126;
		i++;
	}
	free_path(path);
	if (ret == 127)
	{
		char	*error2;
		error2 = ft_strjoin(exec, ": command not found");
		return (pr_error(error2, ret), free(error), free(error2), ret);
	}
	return (pr_error(error, ret), free(error), ret);
}
