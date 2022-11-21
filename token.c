/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:03:45 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/21 17:39:03 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->val = ft_strdup(value);
	return (token);
}

t_list_token	*get_token(t_lexer *lexer, t_list_token *list_token)
{
	t_token *token;
	
	token = NULL;
	if (lexer->c == '\0')
	{
		token = init_token(-1, NULL);
		add_node(&list_token,node(&token));
		return (list_token);
	}
	while (lexer->c != '\0')
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			skip_whitespace(lexer);
		if (lexer->c == '\"' || lexer->c == '\'')
			token = get_quote(lexer);
		else if (lexer->c == '$' || lexer->c == '|')
			token = get_dollar_pipe_token(lexer);
		else if (lexer->c == '>' || lexer->c == '<')
			token = get_redirection_token(lexer);
		else
			token = get_word_token(lexer);
		add_node(&list_token,node(&token));
		while(list_token)
		{
			// printf("type = %d\n",list_token->token->type);
			// printf("value = %s\n\n",list_token->token->val);
			list_token = list_token->next;
		}
	}
	return (list_token);
}


