/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:55:05 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/09 15:46:44 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/**
 * if path is empty look for the exec in the current dir
 * if path is sane look for the exec starting from the first value, if the file
 * 	is found and it is executable, we return a result otherwise throw an error
 * return should be freed
*/
char	*find_exec(char *exec)
{
	char	**path;
	int		i;
	char	*full_path;
	int		path_len;

	if (ft_strchr(exec, '/'))
		return (ft_strdup(exec));
	path = ft_split(get_env("PATH"), ':');
	path_len = path_size(path);
	if (!path_len)
		return (free_path(path), ft_strjoin("./", exec));
	i = 0;
	while (path[i])
	{
		full_path = combine_path_with_exec(path[i], exec);
		if (!access(full_path, F_OK))
		{
			if (!access(full_path, X_OK))
				return (free_path(path), full_path);
			else if (!path[i + 1])
				die(exec, 12);
		}
		free(full_path);
		i++;
	}
	die("command not found", 13);
}
