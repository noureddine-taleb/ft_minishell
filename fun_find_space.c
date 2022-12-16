/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_find_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 22:35:08 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/16 01:36:09 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*get_last_word(char **word, char *tmp)
{
	t_lexer	*arg_to_split;
	char	*last_word;

	last_word = NULL;
	arg_to_split = NULL;
	while (tmp && *tmp)
		last_word = ft_strjoin2(last_word, *tmp++, arg_to_split);
	if (*word)
	{
		ft_free(word);
		*word = last_word;
	}
	return (last_word);
}

void	skip_whitespace_2(int *i, char **tmp)
{
	while (**tmp && is_whitespace(**tmp))
	{
		(*i)++;
		(*tmp)++;
	}
}

void	add_node_in_list(char **tmp, char **arg,
	t_list_token **list_token, t_data **data)
{
	t_lexer	*arg_to_split;

	arg_to_split = NULL;
	if (**tmp && *arg)
	{
		arg_to_split = init_lexer(*arg);
		get_token(arg_to_split, list_token, data);
		ft_free(&(arg_to_split->command_ling));
		free(arg_to_split);
		arg_to_split = NULL;
		*arg = NULL;
	}
}

void	ft_find_space_2(char **tmp, int *i, char **arg)
{
	t_lexer	*arg_to_split;

	arg_to_split = NULL;
	*arg = ft_strjoin2(*arg, **tmp, arg_to_split);
	(*tmp)++;
	(*i)++;
}

void	ft_find_space(char **word, t_list_token **list_token, t_data **data)
{
	char	*tmp;
	char	*tmp_2;
	char	*arg;
	int		i;

	i = 0;
	tmp = *word;
	tmp_2 = *word;
	arg = NULL;
	if (nbr_word(*word) > 1)
	{
		while (tmp && *tmp)
		{
			if (is_whitespace(*tmp))
			{
				skip_whitespace_2(&i, &tmp);
				add_node_in_list(&tmp, &arg, list_token, data);
			}
			else if (nbr_word(tmp) > 1)
				ft_find_space_2(&tmp, &i, &arg);
			else
				break ;
		}
	}
	get_last_word(word, tmp);
}
