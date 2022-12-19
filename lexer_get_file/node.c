/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 08:16:46 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/06 05:55:14 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_token	*node(t_token **token)
{
	t_list_token	*new_token;

	new_token = malloc(sizeof(t_list_token));
	if (!new_token)
		return (NULL);
	new_token->token = *token;
	new_token->next = NULL;
	return (new_token);
}

void	add_node(t_list_token **list_token, t_list_token *new_token)
{
	t_list_token	*tmp;

	tmp = *list_token;
	if (!(*list_token))
		*list_token = new_token;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		(tmp)->next = new_token;
	}
}
