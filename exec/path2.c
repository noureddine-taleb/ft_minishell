/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:14:49 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/17 15:15:33 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * result should be freed
*/
char	*combine_path_with_exec(char *path, char *exec)
{
	char	*full_path;

	if (path[ft_strlen(path) - 1] == '/')
		return (ft_strjoin(path, exec));
	path = ft_strjoin(path, "/");
	full_path = ft_strjoin(path, exec);
	free(path);
	return (full_path);
}

void	free_path(char **path)
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
