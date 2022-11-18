/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:03:45 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/18 03:01:37 by kadjane          ###   ########.fr       */
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
	token->val = value;
	return (token);
}

char	get_next_char (t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer-> index < ft_strlen(lexer->command_ling))
	{
		lexer->index += 1;
		lexer->c = lexer->command_ling[lexer->index];
	}
	return (lexer->c);
}

void	skip_whitespace(t_lexer *lexer)
{
	while((lexer->c != '\0' && lexer->index < ft_strlen(lexer->command_ling))
			&& (lexer->c == ' ' || lexer->c == '\t'))
				get_next_char(lexer);
}

char	**char_convert_string(char c)
{
	char	**string;

	string = malloc(2);
	if (!string)
		return (NULL);
	*(*string) = c;
	*(*(string + 1)) = '\0';
	return (string);
}

t_token	*get_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->index < ft_strlen(lexer->command_ling))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			skip_whitespace(lexer);
		if (lexer->c == '\'')
			init_token(TOKEN_S_QUOTE,*char_convert_string(lexer->c));
		else if (lexer->c == '\"')
			init_token(TOKEN_D_QUOTE,*char_convert_string(lexer->c));
		else if (lexer->c == '<' && get_next_char(lexer) != '<')
			init_token(TOKEN_REDI_INPUT,*char_convert_string('<'));
		else if (lexer->c == '>' && get_next_char(lexer) != '>')
			init_token(TOKEN_REDI_OUTPUT,*char_convert_string(lexer->c));
		else if (lexer->c == '>' && get_next_char(lexer) == '>')
			init_token(TOKEN_APPAND,ft_strjoin(char_convert_string(lexer->c), (lexer->c)));
		else if (lexer->c == '<' && get_next_char(lexer) == '<')
			init_token(TOKEN_HERDOC,ft_strjoin(char_convert_string(lexer->c), (lexer->c)));
		else
		{
			while(((lexer->c > 'a' && lexer->c < 'z') || (lexer->c > 'A' && lexer->c < 'Z')) && lexer->c != '\0')
			{
				
			}
		}
	}
}


