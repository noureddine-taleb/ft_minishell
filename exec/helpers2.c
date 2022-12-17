/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:38:13 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/17 14:54:01 by ntaleb           ###   ########.fr       */
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
