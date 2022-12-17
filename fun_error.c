/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 00:55:11 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/17 14:42:31 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	is_token_2(int type_token)
{
	if (type_token == TOKEN_REDI_OUTPUT || type_token == TOKEN_APPAND
		|| type_token == TOKEN_REDI_INPUT || type_token == TOKEN_HERDOC)
		return (g_state.exit_status = 1);
	return (g_state.exit_status = 0);
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
			return (g_state.exit_status = 1);
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

int	check_ambiguous(t_list_token **list_token, t_data **data)
{
	t_list_token	*tmp;

	tmp = *list_token;
	while (tmp)
	{
		if (((tmp->token->e_type == TOKEN_FILE_OUT
					|| tmp->token->e_type == TOKEN_FILE_INP
					|| tmp->token->e_type == TOKEN_FILE_APPAND)
				&& (*data)->sign_expand)
			|| (*data)->sign_for_ambiguous)
		{
				(*data)->sign_expand = 0;
				(*data)->sign_for_ambiguous = 0;
			return (g_state.exit_status = 1);
		}
		tmp = tmp->next;
	}
	return (g_state.exit_status = 0);
}

int	check_redirection(t_list_token **list_token, t_data **data)
{
	t_list_token	*tmp;

	tmp = *list_token;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp && tmp->token && is_token_2(tmp->token->e_type)
		&& !(*data)->sign_for_ambiguous)
		return (g_state.exit_status = 258);
	return (g_state.exit_status = 0);
}
