/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:03:45 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/16 01:37:47 by kadjane          ###   ########.fr       */
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

char	*get_value(t_lexer *lexer, t_data **data, t_list_token **list_token)
{
	char			*word;
	t_list_token	*tmp_2;

	tmp_2 = *list_token;
	while (tmp_2 && tmp_2->next)
		tmp_2 = tmp_2->next;
	if (lexer->c == '\"')
		return (d_quote(lexer, data, *list_token));
	else if (lexer->c == '\'')
		return (s_quote(lexer, data));
	else if (lexer->c == '|')
		return (get_pipe_token(lexer, data));
	else if (lexer->c == '>' || lexer->c == '<')
		return (get_redirection_token(lexer, data));
	else
	{
		word = get_word_token(lexer, data, list_token);
		if (!word)
		{
			(*data)->sign_expand_2 = 1;
			if (tmp_2 && is_token_2(tmp_2->token->e_type))
				(*data)->sign_for_ambiguous = 1;
		}
		return (word);
	}
}

t_list_token	*get_token(t_lexer *lexer, t_list_token **list_token,
	t_data **data)
{
	t_token	*token;

	token = NULL;
	(*data)->nbr_space = 0;
	(*data)->join_value = NULL;
	(*data)->value = NULL;
	(*data)->sign_exp_digit = 0;
	while (is_whitespace(lexer->c))
		skip_whitespace(lexer);
	get_token_2(list_token, &token, lexer, data);
	add_node(list_token, NULL);
	return (*list_token);
}

t_list_token	*get_token_2(t_list_token **list_token, t_token **token,
		t_lexer *lexer, t_data **data)
{
	while (lexer->c != '\0')
	{
		skip_whitespace(lexer);
		(*data)->value = get_value(lexer, data, list_token);
		if ((*data)->value && is_token((*data)->value)
			&& (*data)->sign_quote)
			(*data)->sign_token = 1;
		if ((*data)->value && is_token((*data)->value)
			&& !(*data)->sign_quote)
			add_token(list_token, data);
		else
		{
			get_token_3(data, lexer);
			if (!((*data)->value) && !(*data)->nbr_space
				&& !(*data)->sign_expand_2)
			{
				add_node(list_token, node(token));
				return (*list_token);
			}
			if (!lexer->c || (*data)->nbr_space || (*data)->sign_find_space)
				add_token_2(list_token, data);
		}
	}
	return (*list_token);
}

void	get_token_3(t_data **data, t_lexer *lexer)
{
	if ((*data)->nbr_space == 0 || (*data)->sign_find_space)
		(*data)->join_value = ft_strjoin((*data)->join_value, (*data)->value);
	if (is_whitespace(lexer->c))
	{
		((*data)->nbr_space)++;
		skip_whitespace(lexer);
	}
}
