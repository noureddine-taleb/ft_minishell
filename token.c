/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:03:45 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/20 04:11:53 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

t_token *init_token(int type, char *value)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->val = ft_strdup(value);
	
	return (token);
}


t_token	*get_token(t_lexer *lexer)
{
	char	*word;
	t_token	*token;

	word = NULL;
	if (*lexer->command_ling == '\0')
	{
		token = init_token(-1, NULL);
		return (token);
	}
	while (lexer->c != '\0' && lexer->index < ft_strlen(lexer->command_ling))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			skip_whitespace(lexer);
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

		else if (lexer->c == '<' && lexer->command_ling[lexer->index + 1] != '<')
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
			token = init_token(TOKEN_APPAND,ft_strjoin(char_convert_string(lexer->c), (lexer->c), lexer));
			get_next_char(lexer);
		}
			
		else if (lexer->c == '<' && lexer->command_ling[lexer->index + 1] == '<')
		{
			token = init_token(TOKEN_HERDOC,ft_strjoin(char_convert_string(lexer->c), (lexer->c), lexer));
			get_next_char(lexer);
		}
		
		else if (lexer->c == '$')
		{
			token = init_token(TOKEN_DOLLAR,char_convert_string(lexer->c));
			get_next_char(lexer);
		}

		else if (lexer->c == '|')
		{
			token = init_token(TOKEN_PIPE,char_convert_string(lexer->c));
			get_next_char(lexer);
		}
		
		else
		{
			while(ft_isalpha(lexer->c))
				word = ft_strjoin(word, lexer->c, lexer);
			token = init_token(TOKEN_WORD, word);
		}
		printf("type = %d\n",token->type);
		printf("value = %s\n\n",token->val);
	}
	return (token);
}


