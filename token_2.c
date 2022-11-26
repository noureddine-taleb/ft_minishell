/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:41:13 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/25 23:45:54 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

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
		string = ft_strjoin2(char_convert_string(lexer->c), lexer);
		get_next_char(lexer);
	}
	else if (lexer->c == '<' && lexer->command_ling[lexer->index + 1] == '<')
	{
		string = ft_strjoin2(char_convert_string(lexer->c), lexer);
		get_next_char(lexer);
	}
	return (string);
}

char *s_quote(t_lexer *lexer)
{
	char	*string;
	
	string = NULL;
	if (lexer->c == '\'')
	{
		get_next_char(lexer);
		while (lexer->c && lexer->c != '\'')
			string = ft_strjoin2(string, lexer);
		if (lexer->c == '\'')
		{ 
			get_next_char(lexer);
			if(string)
				return (string);
			else
				return(ft_strdup(""));
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
	if(lexer->c == '"')
	{
		get_next_char(lexer);
		while (lexer->c && lexer->c != '"')
			string = ft_strjoin2(string, lexer);
		if (lexer->c == '"')
		{ 
			get_next_char(lexer);
			if(string)
				return (string);
			else
				return(ft_strdup(""));
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

int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13 )|| c == ' ')
		return (1);
	return (0);
}

int	is_token(char *lexer)
{
	 
	if (!ft_strcmp(lexer,">") || !ft_strcmp(lexer,">>")
		|| !ft_strcmp(lexer,"<") || !ft_strcmp(lexer,"<<")
		|| !ft_strcmp(lexer,"$") || !ft_strcmp(lexer,"|")
		|| !ft_strcmp(lexer,"'") || !ft_strcmp(lexer,"\""))
			return (1);
	return (0);
}

char	*get_word_token(t_lexer *lexer)
{
	char	*word;
	
	word = NULL;
	while(lexer->c && !is_whitespace(lexer->c) && !is_token(char_convert_string(lexer->c)))
		word = ft_strjoin2(word, lexer);
	return (word);
}