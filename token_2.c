/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:41:13 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/21 17:38:37 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

t_token	*get_redirection_token(t_lexer *lexer)
{
	t_token	*token;
	
	token = NULL;
	if (lexer->c == '<' && lexer->command_ling[lexer->index + 1] != '<')
	{
		token = init_token(TOKEN_REDI_INPUT,char_convert_string('<'));
		get_next_char(lexer);
	}
	else if (lexer->c == '>' && lexer->command_ling[lexer->index + 1] != '>')
	{
		token = init_token(TOKEN_REDI_OUTPUT,char_convert_string(lexer->c));
		get_next_char(lexer);
	}
	else if (lexer->c == '>' && lexer->command_ling[lexer->index + 1] == '>')
	{
		token = init_token(TOKEN_APPAND,ft_strjoin(char_convert_string(lexer->c), lexer));
		get_next_char(lexer);
	}
	else if (lexer->c == '<' && lexer->command_ling[lexer->index + 1] == '<')
	{
		token = init_token(TOKEN_HERDOC,ft_strjoin(char_convert_string(lexer->c), lexer));
		get_next_char(lexer);
	}
	return (token);
}

t_token	*get_quote(t_lexer *lexer)
{
	t_token	*token;
	
	token = NULL;
	if (lexer->c == '\'')
	{
		token = init_token(TOKEN_S_QUOTE,char_convert_string(lexer->c));
		get_next_char(lexer);
	}
	else if (lexer->c == '\"')
	{
		token = init_token(TOKEN_D_QUOTE,char_convert_string(lexer->c));
		get_next_char(lexer);
	}
	return (token);
}

t_token	*get_dollar_pipe_token(t_lexer *lexer)
{
	t_token	*token;
	
	token = NULL;
	if (lexer->c == '$')
	{
		token = init_token(TOKEN_DOLLAR,char_convert_string(lexer->c));
		get_next_char(lexer);
	}
	else if (lexer->c == '|')
	{
		token = init_token(TOKEN_PIPE,char_convert_string(lexer->c));
		get_next_char(lexer);
	}
	return (token);
}

t_token	*get_word_token(t_lexer *lexer)
{
	char	*word;
	t_token	*token;
	
	token = NULL;
	word = NULL;
	printf("char = %c\n", lexer->c);
	while(lexer->c && !get_quote(lexer) 
		&& !get_dollar_pipe_token(lexer) && !get_redirection_token(lexer))
		word = ft_strjoin(word, lexer);
	token = init_token(TOKEN_WORD, word);
	return (token);
}