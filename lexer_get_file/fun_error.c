/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 00:55:11 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/20 11:40:17 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	is_token_2(int type_token)
{
	if (type_token == TOKEN_REDI_OUTPUT || type_token == TOKEN_APPAND
		|| type_token == TOKEN_REDI_INPUT || type_token == TOKEN_HERDOC)
		return (1);
	return (0);
}

int	check_quote_pipe(t_list_token **list_token)
{
	t_list_token	*tmp;
	t_list_token	*tmp_2;

	tmp = *list_token;
	tmp_2 = *list_token;
	while (tmp && tmp->next)
		tmp = tmp->next;
	while (tmp_2)
	{
		if (!tmp_2->token || (tmp->token && !ft_strcmp(tmp->token->val, "|")
				&& tmp->token->e_type == TOKEN_PIPE))
			return (g_state.exit_status = 258);
		tmp_2 = tmp_2->next;
	}
	return (g_state.exit_status = 0);
}

int	check_token(t_list_token **list_token)
{
	t_list_token	*tmp;
	t_list_token	*tmp_2;

	tmp = *list_token;
	tmp_2 = *list_token;
	if (tmp_2 && tmp_2->token && tmp_2->token->e_type == TOKEN_PIPE)
		return (g_state.exit_status = 258);
	while (tmp && tmp->next)
	{
		if (tmp->token
			&& ((is_token_2(tmp->token->e_type)
					&& is_token_2(tmp->next->token->e_type))
				|| (is_token_2(tmp->token->e_type)
					&& tmp->next->token->e_type == TOKEN_PIPE)
				|| (tmp->token->e_type == TOKEN_PIPE
					&& tmp->next->token->e_type == TOKEN_PIPE)))
			return (g_state.exit_status = 258);
		tmp = tmp->next;
	}
	return (g_state.exit_status = 0);
}

int	check_redirection(t_list_token **list_token)
{
	t_list_token	*tmp;

	tmp = *list_token;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp && tmp->token && is_token_2(tmp->token->e_type))
		return (g_state.exit_status = 258);
	return (g_state.exit_status = 0);
}
