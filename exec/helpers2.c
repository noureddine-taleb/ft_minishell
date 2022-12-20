/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:38:13 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/20 17:43:47 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_append_flag(struct s_list_io_stream *io)
{
	if (io->flags == TOKEN_FILE_APPAND)
		return (O_APPEND);
	else
		return (O_TRUNC);
}

int	arr_size(char **arr)
{
	int	len;

	len = 0;
	if (!arr)
		return (0);
	while (*arr)
	{
		len++;
		arr++;
	}
	return (len);
}

void	__set_local(char *name)
{
	char	**new_local;
	int		old_size;

	if (get_local(name) || get_env(name))
		return ;
	if (!g_state.local)
	{
		old_size = 0;
		g_state.local = ft_calloc(2, sizeof(char **));
	}
	else
	{
		old_size = arr_size(g_state.local);
		new_local = ft_calloc(old_size + 2, sizeof(char **));
		ft_memcpy(new_local, g_state.local, old_size * sizeof(char **));
		free(g_state.local);
		g_state.local = new_local;
	}
	g_state.local[old_size] = ft_strdup(name);
}

int	__unset_local(char *name)
{
	char	**local;

	local = g_state.local;
	if (!local)
		return (0);
	while (*local)
	{
		if (!ft_strcmp(name, *local))
		{
			free(*local);
			ft_memmove(local, local + 1, arr_size(local) * sizeof(char **));
			return (1);
		}
		local++;
	}
	return (0);
}

char	*get_local(char *name)
{
	char	**local;

	local = g_state.local;
	if (!local)
		return (NULL);
	while (*local)
	{
		if (!ft_strcmp(name, *local))
			return (*local);
		local++;
	}
	return (NULL);
}
