/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:16:26 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/20 17:27:00 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	convert_type_word_2(t_list_token **list_token)
{
	if ((*list_token)->next->token
		&& (*list_token)->token->e_type == TOKEN_REDI_INPUT)
	{
		if ((*list_token)->next->token->e_type == TOKEN_WORD)
			(*list_token)->next->token->e_type = TOKEN_FILE_INP;
	}
	if ((*list_token)->next->token && (*list_token)->next
		&& (*list_token)->token->e_type == TOKEN_HERDOC)
	{
		if ((*list_token)->next->token->e_type == TOKEN_WORD)
			(*list_token)->next->token->e_type = TOKEN_FILE_HERDOC;
	}
}

void	convert_type_word(t_list_token **list_token)
{
	t_list_token	*tmp;

	tmp = *list_token;
	while (tmp && tmp->next)
	{
		if (tmp->next->token && tmp->token->e_type == TOKEN_REDI_OUTPUT)
		{
			if (tmp->next->token->e_type == TOKEN_WORD)
				tmp->next->token->e_type = TOKEN_FILE_OUT;
		}
		if (tmp->next->token && tmp->token->e_type == TOKEN_APPAND)
		{
			if (tmp->next->token->e_type == TOKEN_WORD)
				tmp->next->token->e_type = TOKEN_FILE_APPAND;
		}
		convert_type_word_2(&tmp);
		tmp = tmp->next;
	}
}

int	nbr_args(t_list_token *list_token)
{
	int				i;
	t_list_token	*tmp;

	i = 0;
	tmp = list_token;
	while (tmp && tmp->token && tmp->token->e_type != TOKEN_PIPE)
	{
		if (tmp->token->e_type == TOKEN_WORD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

// int	len_list(t_list_token **list_cmd)
// {
// 	t_list_token	*tmp;
// 	int				i;

// 	i = 0;
// 	tmp = *list_cmd;
// 	while (tmp)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

// int	len_list(t_list_cmd **list_cmd)
// {
// 	t_list_cmd		*tmp;
// 	int				i;

// 	i = 0;
// 	tmp = *list_cmd;
// 	while (tmp)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

void	init_node(t_list_cmd **new_cmd)
{
	(*new_cmd)->cmds_args = NULL;
	(*new_cmd)->io = NULL;
	(*new_cmd)->next = NULL;
}
