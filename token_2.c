/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:41:13 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/29 12:54:15 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*get_redirection_token(t_lexer *lexer)
{
	char	*string;

	string = NULL;
	if (lexer->c == '<' && lexer->command_ling[lexer->index + 1] != '<')
	{
		string = char_convert_string('<');
		get_next_char(lexer);
	}
	else if (lexer->c == '>' && lexer->command_ling[lexer->index + 1] != '>')
	{
		string = char_convert_string('>');
		get_next_char(lexer);
	}
	else if (lexer->c == '>' && lexer->command_ling[lexer->index + 1] == '>')
	{
		string = ft_strjoin2(char_convert_string(lexer->c), lexer->c, lexer);
		get_next_char(lexer);
	}
	else if (lexer->c == '<' && lexer->command_ling[lexer->index + 1] == '<')
	{
		string = ft_strjoin2(char_convert_string(lexer->c), lexer->c, lexer);
		get_next_char(lexer);
	}
	return (string);
}

char	*s_quote(t_lexer *lexer)
{
	char	*string;

	string = NULL;
	if (lexer->c == '\'')
	{
		get_next_char(lexer);
		while (lexer->c && lexer->c != '\'')
			string = ft_strjoin2(string, lexer->c, lexer);
		if (lexer->c == '\'')
		{
			get_next_char(lexer);
			if (string)
				return (string);
			else
				return (ft_strdup(""));
		}
		else
		{
			free (string);
			string = NULL;
		}
	}
	return (string);
}

char	*d_quote(t_lexer *lexer)
{
	char	*string;

	string = NULL;
	if (lexer->c == '"')
	{
		get_next_char(lexer);
		while (lexer->c && lexer->c != '"')
			string = ft_strjoin2(string, lexer->c, lexer);
		if (lexer->c == '"')
		{
			get_next_char(lexer);
			if (string)
				return (string);
			else
				return (ft_strdup(""));
		}
		else
		{
			free (string);
			string = NULL;
		}
	}
	return (string);
}

char	*get_dollar_pipe_token(t_lexer *lexer)
{
	char	*string;

	string = NULL;
	if (lexer->c == '$' || lexer->c == '|')
	{
		string = char_convert_string(lexer->c);
		get_next_char(lexer);
	}
	return (string);
}

char	*get_word_token(t_lexer *lexer, t_data **data)
{
	char	*word;
	char	*new_word;
	char	*str;

	word = NULL;
	(void)data;
	while (lexer->c && !is_whitespace(lexer->c))
	{
		str = char_convert_string(lexer->c);
		if (!is_token(str))
		{
			if (lexer->c == '$')
			{
				new_word = ft_expand(word, lexer, data);
				if(new_word)
				{
					ft_free(&word);
					word = new_word;
				}
				else
				{
					get_next_char(lexer);
					while(!is_token(&lexer->c) && lexer->c != '$')
						get_next_char(lexer);
				}
			}
			else
				word = ft_strjoin2(word, lexer->c, lexer);
		}
		else
		{
			ft_free(&str);
			break ;
		}
	}
	return (word);
}
