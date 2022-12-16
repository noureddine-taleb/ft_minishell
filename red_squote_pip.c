/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_squote_pip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:01:55 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/16 01:44:29 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	get_redirection_token_2(t_lexer *lexer, char **string)
{
	if (lexer->c == '>' && lexer->command_ling[lexer->index + 1] == '>')
	{
		*string = ft_strjoin2(char_convert_string(lexer->c), lexer->c, lexer);
		get_next_char(lexer);
	}
	else if (lexer->c == '<' && lexer->command_ling[lexer->index + 1] == '<')
	{
		*string = ft_strjoin2(char_convert_string(lexer->c), lexer->c, lexer);
		get_next_char(lexer);
	}
}

char	*get_redirection_token(t_lexer *lexer, t_data **data)
{
	char	*string;

	string = NULL;
	(*data)->sign_quote = 0;
	(*data)->sign_d_s_quote = 0;
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
	else
		get_redirection_token_2(lexer, &string);
	return (string);
}

char	*s_quote(t_lexer *lexer, t_data **data)
{
	char	*string;

	string = NULL;
	if (lexer->c == '\'')
	{
		(*data)->sign_d_s_quote = 1;
		(*data)->sign_expand_2 = 0;
		get_next_char(lexer);
		while (lexer->c && lexer->c != '\'')
			string = ft_strjoin2(string, lexer->c, lexer);
		if (lexer->c == '\'')
		{
			(*data)->sign_quote = 1;
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

char	*get_pipe_token(t_lexer *lexer, t_data **data)
{
	char	*string;

	(*data)->sign_quote = 0;
	string = char_convert_string(lexer->c);
	get_next_char(lexer);
	skip_whitespace(lexer);
	return (string);
}
