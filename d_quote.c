/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 01:57:49 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/16 00:33:37 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*d_quote(t_lexer *lexer, t_data **data, t_list_token *list_token)
{
	char	*string;

	string = NULL;
	if (lexer->c == '"')
	{
		get_next_char(lexer);
		string = d_quote_3(lexer, data, &string, list_token);
		if (lexer->c == '"')
		{
			(*data)->sign_quote = 1;
			(*data)->sign_d_s_quote = 1;
			(*data)->sign_expand_2 = 0;
			get_next_char(lexer);
			if (string)
				return (string);
			else
				return (ft_strdup(""));
		}
		else
			ft_free (&string);
	}
	return (string);
}

char	*d_quote_2(t_lexer *lexer, char *string, t_data **data)
{
	char	*new_string;

	new_string = ft_expand(string, lexer, data);
	if (new_string)
	{
		ft_free(&string);
		string = new_string;
	}
	else
	{
		if (!(*data)->sign_exp_digit)
		{
			get_next_char(lexer);
			while (lexer->c && lexer->c != '$' && lexer->c != '"'
				&& !is_whitespace(lexer->c) && ft_isalnum(lexer->c))
				get_next_char(lexer);
		}
		else
			(*data)->sign_exp_digit = 0;
	}
	return (string);
}

char	*d_quote_3(t_lexer *lexer, t_data **data, char **string,
	t_list_token *list_token)
{
	while (list_token && list_token->next)
		list_token = list_token->next;
	while (lexer->c && lexer->c != '"')
	{
		if ((lexer->c == '$' && list_token
				&& ft_strcmp(list_token->token->val, "<<"))
			|| (!list_token && lexer->c == '$'))
			*string = d_quote_2(lexer, *string, data);
		else
			*string = ft_strjoin2(*string, lexer->c, lexer);
	}
	return (*string);
}
