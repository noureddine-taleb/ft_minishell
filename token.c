/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:03:45 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/02 01:46:45 by kadjane          ###   ########.fr       */
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

int	is_token(char *lexer)
{
	if (lexer && (!ft_strcmp(lexer, ">") || !ft_strcmp(lexer, ">>")
			|| !ft_strcmp(lexer, "<") || !ft_strcmp(lexer, "<<")
			|| !ft_strcmp(lexer, "|") || !ft_strcmp(lexer, "'")
			|| !ft_strcmp(lexer, "\"")))
		return (1);
	return (0);
}

char	*get_value(t_lexer *lexer, t_data **data)
{
	char	*word;
	if (lexer->c == '$' && lexer->command_ling[lexer->index + 1] == '"')
	{
		get_next_char(lexer);
		return(d_quote(lexer, data));
	}
	else if (lexer->c == '\"')
		return (d_quote(lexer, data));
	else if (lexer->c == '\'')
		return (s_quote(lexer));
	else if (lexer->c == '|')
		return (get_pipe_token(lexer));
	else if (lexer->c == '>' || lexer->c == '<')
		return (get_redirection_token(lexer));
	else
	{
		word = get_word_token(lexer, data);
		if(!word)
			return(ft_strdup(""));
		return (word);
	}
}

t_list_token	*get_token(t_lexer *lexer, t_list_token *list_token, t_data **data)
{
	t_token		*token;

	token = NULL;
	(*data)->nbr_space = 0;
	(*data)->join_value = NULL;
	(*data)->value = NULL;
	while (is_whitespace(lexer->c))
		skip_whitespace(lexer);
	list_token = get_token_2(list_token, &token, lexer, data);
	add_node(&list_token, NULL);
	return (list_token);
}

t_list_token	*get_token_2(t_list_token *list_token, t_token **token,
		t_lexer *lexer, t_data **data)
{
	while (lexer->c != '\0')
	{
		skip_whitespace(lexer);
		(*data)->value = get_value(lexer, data);
		if ((*data)->value && is_token((*data)->value))
			add_token(&list_token, data);
		else
		{
			if ((*data)->nbr_space == 0)
				(*data)->join_value = ft_strjoin((*data)->join_value, (*data)->value);
			if (is_whitespace(lexer->c))
			{
				((*data)->nbr_space)++;
				skip_whitespace(lexer);
			}
			if (!((*data)->value) && !(*data)->nbr_space)
			{
				add_node(&list_token, node(token));
				return (list_token);
			}
			if (!lexer->c || (*data)->nbr_space)
				add_token_2(&list_token, data);
		}
	}
	return (list_token);
}
