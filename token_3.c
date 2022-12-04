/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 22:04:40 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/04 00:57:29 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	get_type_token(char *value, t_data **data)
{
	if (!value)
		return (-1);
	// printf("-------> sign == %d\n",(*data)->sign_d_quote);
	if(!(*data)->sign_d_quote)
	{
		if (!ft_strcmp(value, ">"))
			return (TOKEN_REDI_INPUT);
		if (!ft_strcmp(value, "<"))
			return (TOKEN_REDI_OUTPUT);
		if (!ft_strcmp(value, "<<"))
			return (TOKEN_HERDOC);
		if (!ft_strcmp(value, ">>"))
			return (TOKEN_APPAND);
		if (!ft_strcmp(value, "|"))
			return (TOKEN_PIPE);
	}
	return (TOKEN_WORD);
}

void	add_token(t_list_token **list_token, t_data **data)
{
	t_token		*token;
	int			type_token;

	if ((*data)->join_value)
	{
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
	t_token	*token;
	int		type_token;

	(*data)->nbr_space = 0;
	if ((*data)->join_value)
	{
		type_token = get_type_token((*data)->join_value, data);
		token = init_token(type_token, (*data)->join_value);
		ft_free (&((*data)->join_value));
		ft_free(&((*data)->value));
		add_node(list_token, node(&token));
	}
	(*data)->sign_d_quote = 0;
}

int	is_token(char *lexer)
{
	if (lexer && (!ft_strcmp(lexer, ">") || !ft_strcmp(lexer, ">>")
			|| !ft_strcmp(lexer, "<") || !ft_strcmp(lexer, "<<")
			|| !ft_strcmp(lexer, "|") || !ft_strcmp(lexer, "'")
			|| !ft_strcmp(lexer, "\"")))
		return (1);
	return (0);
}