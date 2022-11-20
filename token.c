/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:03:45 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/20 10:05:23 by kadjane          ###   ########.fr       */
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

t_token *get_redirection_token(t_lexer *lexer, t_token *token)
{
	
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

int	check_is_token(char *c)
{
	if (c == '\'' || c == '\"' || c == '$'
		c == '|' || c == '>' || c == '<')
}
t_token	*get_word_token(t_lexer *lexer, t_token *token)
{
	char	*word;
	
	word = NULL;
	if (word)
	{
		free (word);
		word = NULL;
	}
	while(lexer->c && !get_quote(lexer, token) 
		&& !get_dollar_pipe_token(lexer, token) && !get_redirection_token(lexer, token))
	{
		// skip_whitespace(lexer);
		word = ft_strjoin(word, lexer);
	}
	token = init_token(TOKEN_WORD, word);
	return (token);
}

t_token	*get_quote(t_lexer *lexer, t_token *token)
{
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

t_token	*get_dollar_pipe_token(t_lexer *lexer, t_token *token)
{

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

t_list_token	*get_token(t_lexer *lexer,t_token *token, t_list_token *list_token)
{

	if (lexer->c == '\0')
	{
		token = init_token(-1, NULL);
		add_node(&list_token,node(&token));
		return (list_token);
	}
	while (lexer->c != '\0' && lexer->index < ft_strlen(lexer->command_ling))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			skip_whitespace(lexer);
		if (lexer->c == '\"' || lexer->c == '\'')
			token = get_quote(lexer, token);
		else if (lexer->c == '$' || lexer->c == '|')
			token = get_dollar_pipe_token(lexer, token);
		else if (lexer->c == '>' || lexer->c == '<')
			token = get_redirection_token(lexer, token);
		else
			token = get_word_token(lexer, token);
		add_node(&list_token,node(&token));
		while(list_token)
		{
			printf("type = %d\n",list_token->token->type);
			printf("value = %s\n\n",list_token->token->val);
			list_token = list_token->next;
		}
		// printf("type = %d\n",token->type);
		// printf("value = %s\n",token->val);
	}
	return (list_token);
}


