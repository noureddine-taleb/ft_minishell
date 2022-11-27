/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:03:45 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/28 00:38:21 by kadjane          ###   ########.fr       */
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
		return (d_quote(lexer));
	else if (lexer->c == '\'')
		return (s_quote(lexer));
	else if (lexer->c == '$' || lexer->c == '|')
		return (get_dollar_pipe_token(lexer));
	else if (lexer->c == '>' || lexer->c == '<')
		return (get_redirection_token(lexer));
	else
		return (get_word_token(lexer));
}

t_list_token	*get_token(t_lexer *lexer, t_list_token *list_token)
{
	t_token		*token;
	t_data		data;

	token = NULL;
	data.nbr_space = 0;
	data.join_value = NULL;
	data.value = NULL;
	while (is_whitespace(lexer->c))
		skip_whitespace(lexer);
	list_token = get_token_2(list_token, &token, lexer, &data);
	add_node(&list_token, NULL);
	return (list_token);
}

t_list_token	*get_token_2(t_list_token *list_token, t_token **token,
		t_lexer *lexer, t_data *data)
{
	while (lexer->c != '\0')
	{
		data->value = get_value(lexer);
		if (data->value && is_token(data->value))
			add_token(&list_token, data);
		else
		{
			if (data->nbr_space == 0)
				data->join_value = ft_strjoin(data->join_value, data->value);
			if (is_whitespace(lexer->c))
			{
				(data->nbr_space)++;
				skip_whitespace(lexer);
			}
			if (!(data->value) && !data->nbr_space)
			{
				add_node(&list_token, node(token));
				return (list_token);
			}
			if (!lexer->c || data->nbr_space)
				add_token_2(&list_token, data);
		}
		ft_free(&data->value);
	}
	return (list_token);
}
