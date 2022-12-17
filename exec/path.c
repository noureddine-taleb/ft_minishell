/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:55:05 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/17 15:56:57 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*combine_path_with_exec(char *path, char *exec);
void	free_path(char **path);

int	check_exec(char	*exec)
{
	if (access(exec, F_OK) < 0)
		return (-127);
	if (access(exec, X_OK) < 0)
		return (-126);
	return (0);
}

/**
 * this routine looks for the exec following the shell semantics
 * if the exec is found and is executable it returns the success 
 * and the full path is stored in `full_path`
 * otherwise it prints an error and returns the error code
 * 
 * if path is empty look for the exec in the current dir
 * otherwise look for the exec in path
 * 
 * if a file exist but not executable skip it
 * but remember the first instance that exists but not executable,
 * this value will be showen in the error message.
 * 
*/
void	__handle_error(char *exec, char *perm_error, int ret)
{
	if (ret == -127)
		__pr_error(exec, NULL, "command not found", ret);
	else
		pr_error(perm_error, NULL, ret);
}

int	__search_for_exec(char *exec, char **path, char **result)
{
	int		i;
	int		ret;
	char	*perm_error;

	perm_error = NULL;
	i = 0;
	while (path[i])
	{
		*result = combine_path_with_exec(path[i], exec);
		ret = check_exec(*result);
		if (!ret)
			return (0);
		if (ret == -126 && !perm_error)
			perm_error = *result;
		else
			free(*result);
		i++;
	}
	return (__handle_error(exec, perm_error, ret), free(perm_error), ret);
}

int	find_exec(char *exec, char **full_path)
{
	char	**path;
	int		ret;

	path = ft_split(get_env("PATH"), ':');
	if (ft_strchr(exec, '/') || !arr_size(path))
	{
		ret = check_exec(exec);
		if (ret < 0)
			return (pr_error(exec, NULL, ret));
		if (!ft_strchr(exec, '/'))
			*full_path = ft_strjoin("./", exec);
		else
			*full_path = ft_strdup(exec);
		return (free_path(path), 0);
	}
	ret = __search_for_exec(exec, path, full_path);
	return (free_path(path), ret);
}
