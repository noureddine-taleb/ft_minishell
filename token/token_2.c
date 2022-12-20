/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 02:05:26 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/20 14:36:30 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	get_type_token(char *value, t_data **data)
{
	if (!value)
		return (-1);
	if (!(*data)->sign_quote && !(*data)->sign_for_ambiguous)
	{
		if (!ft_strcmp(value, ">"))
			return (TOKEN_REDI_OUTPUT);
		if (!ft_strcmp(value, "<"))
			return (TOKEN_REDI_INPUT);
		if (!ft_strcmp(value, "<<"))
			return (TOKEN_HERDOC);
		if (!ft_strcmp(value, ">>"))
			return (TOKEN_APPAND);
		if (!ft_strcmp(value, "|"))
			return (TOKEN_PIPE);
	}
	else if ((*data)->sign_for_ambiguous)
	{
		(*data)->sign_for_ambiguous = 0;
		return (TOKEN_AMBIGUOUS_REDIRECTION);
	}
	return (TOKEN_WORD);
}

void	add_token(t_list_token **list_token, t_data **data)
{
	t_token		*token;
	int			type_token;

	if ((*data)->join_value)
	{
		if ((*data)->sign_token)
			type_token = TOKEN_WORD;
		else
			type_token = get_type_token((*data)->join_value, data);
		token = init_token(type_token, (*data)->join_value);
		ft_free(&((*data)->join_value));
		add_node(list_token, node(&token));
	}
	if ((*data)->value)
	{
		type_token = get_type_token((*data)->value, data);
		token = init_token(type_token, (*data)->value);
		ft_free(&((*data)->value));
		add_node(list_token, node(&token));
	}
}

void	add_token_2(t_list_token **list_token, t_data **data)
{
	t_token			*token;
	int				type_token;
	t_list_token	*tmp;

	tmp = end_list(list_token);
	if ((*data)->sign_find_space)
		remove_space(&(*data)->join_value);
	if (!(*data)->join_value && tmp && (tmp->token->e_type == TOKEN_REDI_OUTPUT
			|| tmp->token->e_type == TOKEN_APPAND
			|| tmp->token->e_type == TOKEN_REDI_INPUT))
		type_token = TOKEN_AMBIGUOUS_REDIRECTION;
	else
		type_token = get_type_token((*data)->join_value, data);
	token = init_token(type_token, (*data)->join_value);
	add_node(list_token, node(&token));
	if ((*data)->join_value)
		ft_free (&((*data)->join_value));
	if ((*data)->value)
		ft_free(&(*data)->value);
	(*data)->nbr_space = 0;
	(*data)->sign_quote = 0;
	(*data)->sign_find_space = 0;
}

int	is_token(char *lexer)
{
	return (lexer && (!ft_strcmp(lexer, ">") || !ft_strcmp(lexer, ">>")
			|| !ft_strcmp(lexer, "<") || !ft_strcmp(lexer, "<<")
			|| !ft_strcmp(lexer, "|") || !ft_strcmp(lexer, "'")
			|| !ft_strcmp(lexer, "\"")));
}
