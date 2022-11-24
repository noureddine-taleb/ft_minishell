/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:03:45 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/24 21:59:31 by kadjane          ###   ########.fr       */
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
	char		*value;
	char		*join_value;
	int		nbr_space;
	
	value = NULL;
	join_value = NULL;
	while (lexer->c == ' ' || lexer->c == '\t')
		skip_whitespace(lexer);
	nbr_space = 0;
	while (lexer->c != '\0')
	{
		if (lexer->c == '\"')
			value = d_quote(lexer);
		else if (lexer->c == '\'')
			value = s_quote(lexer);
		else if (lexer->c == '$' || lexer->c == '|')
			value = get_dollar_pipe_token(lexer);
		else if (lexer->c == '>' || lexer->c == '<')
			value = get_redirection_token(lexer);
		else
			value = get_word_token(lexer);
		if(nbr_space == 0)
			join_value = ft_strjoin(join_value, value);

		printf("join_value = %s\n\n",join_value);
		if (lexer->c == ' ' || lexer->c == '\t')
		{
			nbr_space++;
			skip_whitespace(lexer);
		}
		if (!lexer->c || nbr_space || !value)
		{
			nbr_space = 0;
			if (!value)
				token = init_token(TOKEN_WORD, NULL);
			else
				token = init_token(TOKEN_WORD, join_value);
			free (join_value);
			free(value);
			value = NULL;
			join_value = NULL;
			add_node(&list_token,node(&token));
		}
	}
	token = init_token(-1, NULL);
	add_node(&list_token,node(&token));
	return (list_token);
}
