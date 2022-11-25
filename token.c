/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:03:45 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/25 20:04:11 by kadjane          ###   ########.fr       */
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

int	get_type_token(char *value)
{
	if (!value)
		return (-1);
	if (!ft_strcmp(value,">"))
		return (TOKEN_REDI_INPUT);
	if (!ft_strcmp(value,"<"))
		return (TOKEN_REDI_OUTPUT);
	if (!ft_strcmp(value,"<<"))
		return (TOKEN_HERDOC);
	if (!ft_strcmp(value,">>"))
		return (TOKEN_APPAND);
	if (!ft_strcmp(value,"|"))
		return (TOKEN_PIPE);
	if (!ft_strcmp(value,"$"))
		return (TOKEN_DOLLAR);
	return(TOKEN_WORD);
}
void	ft_free(char **value)
{
	free (*value);
	*value = NULL;
}

t_list_token	*get_token(t_lexer *lexer, t_list_token *list_token)
{
	t_token *token;
	char		*value;
	char		*join_value;
	int		nbr_space;
	int		type_token;
	
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
		// printf("value = %s\n",value);
		// printf("\033[94mis_token = %d\n\033[00m",is_token(value));
		if (value && is_token(value))
		{
			if (join_value)
			{
				type_token = get_type_token(join_value);
				token = init_token(type_token, join_value);
				ft_free(&join_value);
				add_node(&list_token,node(&token));
			}
			type_token = get_type_token(value);
			token = init_token(type_token, value);
			ft_free(&value);
			add_node(&list_token,node(&token));
		}
		else
		{
			if(nbr_space == 0)
			{
				join_value = ft_strjoin(join_value, value);
				type_token = get_type_token(join_value);
				// printf("join_value = %s\n",join_value);
			}
			if (lexer->c == ' ' || lexer->c == '\t')
			{
				nbr_space++;
				skip_whitespace(lexer);
			}
			if (!value)
			{
				token = NULL;
				add_node(&list_token,node(&token));
				return (list_token);
			}
			if (!lexer->c || nbr_space)
			{
				nbr_space = 0;
				token = init_token(type_token, join_value);
				free (join_value);
				free(value);
				value = NULL;
				join_value = NULL;
				add_node(&list_token,node(&token));
			}
			
		}
	}
	token = init_token(-1, NULL);
	add_node(&list_token,node(&token));
	return (list_token);
}
