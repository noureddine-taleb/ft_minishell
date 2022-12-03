/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:41:13 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/03 23:54:11 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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
		if (lexer->c != '"')
			get_next_char(lexer);
		while (lexer->c != '$' && lexer->c != '"' && lexer->c
			&& !is_whitespace(lexer->c))
			get_next_char(lexer);
	}
	return (string);
}

char	*d_quote(t_lexer *lexer, t_data **data)
{
	char	*string;

	string = NULL;
	if (lexer->c == '"')
	{
		get_next_char(lexer);
		while (lexer->c && lexer->c != '"')
		{
			if (lexer->c == '$')
				string = d_quote_2(lexer, string, data);
			else
				string = ft_strjoin2(string, lexer->c, lexer);
		}
		if (lexer->c == '"')
		{
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

void	get_word_token_3(t_lexer *lexer)
{
	char	*str;

	get_next_char(lexer);
	str = char_convert_string(lexer->c);
	while (lexer->c && ft_isalnum(lexer->c) && !is_token(str)
		&& lexer->c != '$' && !is_whitespace(lexer->c))
	{
		get_next_char(lexer);
		ft_free(&str);
		str = char_convert_string(lexer->c);
	}
}

char	*get_word_token_2(t_lexer *lexer, t_data **data, char **word)
{
	char	*new_word;

	if (lexer->c == '$')
	{
		if (lexer->command_ling[lexer->index + 1] == '"')
		{
			get_next_char(lexer);
			*word = ft_strjoin(*word, d_quote(lexer, data));
		}
		else
		{
			new_word = ft_expand(*word, lexer, data);
			if (new_word)
			{
				ft_free(word);
				*word = new_word;
			}
			else
				get_word_token_3(lexer);
		}
	}
	else
		*word = ft_strjoin2(*word, lexer->c, lexer);
	return (*word);
}

char	*get_word_token(t_lexer *lexer, t_data **data)
{
	char	*word;
	char	*str;

	word = NULL;
	while (lexer->c && !is_whitespace(lexer->c))
	{
		str = char_convert_string(lexer->c);
		if (!is_token(str))
		{
			ft_free(&str);
			get_word_token_2(lexer, data, &word);
		}
		else
		{
			ft_free(&str);
			break ;
		}
	}
	return (word);
}
