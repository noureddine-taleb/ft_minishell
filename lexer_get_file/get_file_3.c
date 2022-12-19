/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:17:42 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/16 01:28:11 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	add_node_file(t_list_io_stream **inpt_out_file,
	t_list_io_stream *new_file)
{
	t_list_io_stream	*tmp;

	tmp = *inpt_out_file;
	if (!(*inpt_out_file))
		*inpt_out_file = new_file;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		(tmp)->next = new_file;
	}
}

t_list_io_stream	*get_io_file(int flags, char **name_file)
{
	t_list_io_stream	*new_file;

	new_file = malloc(sizeof(t_list_io_stream));
	new_file->flags = flags;
	new_file->target = *name_file;
	new_file->next = NULL;
	return (new_file);
}

int	is_file(int type_token)
{
	if (type_token == TOKEN_FILE_APPAND || type_token == TOKEN_FILE_INP
		|| type_token == TOKEN_FILE_OUT)
		return (1);
	return (0);
}

int	find_pipe(t_list_token **list_token)
{
	if (list_token && *list_token && (*list_token)->token
		&& (*list_token)->token->e_type != TOKEN_PIPE)
		return (0);
	return (1);
}
