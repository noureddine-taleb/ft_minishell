/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 00:38:18 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/16 00:46:44 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	nbr_word(char *str)
{
	int	i;

	i = 0;
	while (str && *str)
	{
		while (*str && is_whitespace(*str))
			str++;
		if (*str)
			i++;
		while (*str && !is_whitespace(*str))
			str++;
	}
	return (i);
}

void	find_space_in_word(char **word, t_data **data)
{
	char			*tmp_2;

	tmp_2 = *word;
	while (tmp_2 && *tmp_2)
	{
		if (is_whitespace(*tmp_2))
		{
			(*data)->sign_find_space++;
			break ;
		}
		tmp_2++;
	}
}

t_list_token	*end_list(t_list_token **list_token)
{
	t_list_token	*tmp;

	tmp = *list_token;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	check_space_in_word(char **word, t_list_token *tmp, t_data **data)
{
	if (tmp && nbr_word(*word) > 1
		&& (!ft_strcmp(tmp->token->val, ">")
			|| !ft_strcmp(tmp->token->val, ">>")
			|| !ft_strcmp(tmp->token->val, "<")))
		(*data)->sign_expand = 1;
}

int	found_quote(t_lexer *lexer)
{
	if (lexer->command_ling[lexer->index + 1] == '"'
		|| lexer->command_ling[lexer->index + 1] == '\'')
		return (1);
	return (0);
}
