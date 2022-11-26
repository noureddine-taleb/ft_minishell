/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:03:45 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/27 00:14:03 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->e_type = type;
	token->val = ft_strdup(value);
	return (token);
}

char	*get_value(t_lexer *lexer)
{
	if (lexer->c == '\"')
		return(d_quote(lexer));
	else if (lexer->c == '\'')
		return(s_quote(lexer));
	else if (lexer->c == '$' || lexer->c == '|')
		return(get_dollar_pipe_token(lexer));
	else if (lexer->c == '>' || lexer->c == '<')
		return(get_redirection_token(lexer));
	else
		return(get_word_token(lexer));
}

t_list_token	*get_token(t_lexer *lexer, t_list_token *list_token)
{
	t_token		*token;
	int			nbr_space;


	printf("-----> hna\n");
	token = NULL;
	nbr_space = 0;
	while (is_whitespace(lexer->c))
		skip_whitespace(lexer);
	list_token = get_token_2(list_token, &token, lexer,/*, &join_value, &value,*/ &nbr_space);
	add_node(&list_token, NULL);
	return (list_token);
}	

t_list_token	*get_token_2(t_list_token *list_token, t_token **token, t_lexer *lexer, int *nbr_space)
{
	(*token)->join_value = NULL;
	while (lexer->c != '\0')
	{
		(*token)->value = get_value(lexer);
		if ((*token)->value && is_token((*token)->value))
			add_token(&list_token, &(*token)->join_value, &(*token)->value);
		else
		{
			if(*nbr_space == 0)
				(*token)->join_value = ft_strjoin((*token)->join_value, (*token)->value);
			if (is_whitespace(lexer->c))
			{
				(*nbr_space)++;
				skip_whitespace(lexer);
			}
			if (!(*token)->value)
			{
				add_node(&list_token,node(token));
				return (list_token);
			}
			if (!lexer->c || *nbr_space)
				add_token_2(&list_token, &(*nbr_space), &(*token)->join_value, &(*token)->value );
		}
	}
	return (list_token);
}


