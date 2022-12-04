/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 02:02:10 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/04 02:11:36 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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