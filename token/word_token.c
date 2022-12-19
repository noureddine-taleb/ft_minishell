/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 02:02:10 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/17 13:00:38 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*get_word_token(t_lexer *lexer, t_data **data,
	t_list_token **list_token)
{
	char	*word;

	word = NULL;
	(*data)->sign_find_space = 0;
	while (lexer->c && !is_whitespace(lexer->c))
	{
		if (!is_token((char []){lexer->c, 0}))
		{
			get_word_token_2(lexer, data, &word, list_token);
			if ((*data)->sign_find_space)
				break ;
		}
		else
			break ;
	}
	return (word);
}

char	*get_word_token_2(t_lexer *lexer, t_data **data, char **word,
	t_list_token **list_token)
{
	char			*new_word;
	t_list_token	*tmp;

	tmp = end_list(list_token);
	if ((lexer->c == '$' && tmp && ft_strcmp(tmp->token->val, "<<"))
		|| (!tmp && lexer->c == '$'))
	{
		if (found_quote(lexer))
			*word = get_word_token_3(lexer, data, word, tmp);
		else
		{
			new_word = ft_expand(*word, lexer, data);
			if (new_word)
			{
				ft_free(word);
				*word = new_word;
				get_word_token_4(lexer, data, word, list_token);
			}
			else
				get_word_token_5(lexer, data);
		}
	}
	else
		*word = ft_strjoin2(*word, lexer->c, lexer);
	return (check_space_in_word(word, tmp, data), *word);
}

char	*get_word_token_3(t_lexer *lexer, t_data **data, char **word,
	t_list_token *tmp)
{
	if (lexer->command_ling[lexer->index + 1] == '"')
	{
		get_next_char(lexer);
		*word = ft_strjoin(*word, d_quote(lexer, data, tmp));
	}
	else if (lexer->command_ling[lexer->index + 1] == '\'')
	{
		get_next_char(lexer);
		*word = ft_strjoin(*word, s_quote(lexer, data));
	}
	return (*word);
}

void	get_word_token_4(t_lexer *lexer, t_data **data, char **word,
	t_list_token **list_token)
{
	t_list_token	*tmp;

	tmp = end_list(list_token);
	if (!tmp || (tmp && ft_strcmp(tmp->token->val, ">")
			&& ft_strcmp(tmp->token->val, ">>")
			&& ft_strcmp(tmp->token->val, "<")))
		{
			ft_find_space(word, list_token, data);
			find_space_in_word(word, data);
		}


	else if (tmp && (!ft_strcmp(tmp->token->val, ">")
			|| !ft_strcmp(tmp->token->val, ">>")
			|| !ft_strcmp(tmp->token->val, "<")) && nbr_word(*word) > 1)
			(*data)->sign_for_ambiguous++;
	else if (nbr_word(*word) == 1 && (!lexer->c || is_whitespace(lexer->c)))
		remove_space(word);
}

void	get_word_token_5(t_lexer *lexer, t_data **data)
{
	if (!(*data)->sign_exp_digit)
	{
		get_next_char(lexer);
		while (lexer->c && ft_isalnum(lexer->c) && !is_token(&lexer->c)
			&& lexer->c != '$' && !is_whitespace(lexer->c))
			get_next_char(lexer);
	}
	else
		(*data)->sign_exp_digit = 0;
}
