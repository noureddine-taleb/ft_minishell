/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_herdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:18:32 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/17 14:00:15 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char *ft_readline(char *prompt)
{
	char	*ret;
	char	*ret_2;

	ret = readline(prompt);
	ret_2 = ft_strjoin(ret, "\n");
	ft_free (&ret);
	return (ret_2);
}

char	*ft_herdoc(char *eof, t_data **data, t_lexer *lexer)
{
	char	*string_inp;
	char	*string_join;
	char	*ret_expand;
	char	*tmp;

	ret_expand = NULL;
	string_join = NULL;
	string_inp = ft_readline("> ");
	eof = ft_strjoin(eof, "\n");
	while (string_inp && ft_strcmp(string_inp, eof))
	{
		tmp = string_inp;
		while (tmp && *tmp)
		{
			if (*tmp == '$' && !(*data)->sign_d_s_quote)
			{
				ret_expand = ft_expand_herdoc(string_join, &tmp, data);
				ft_herdoc_2(&ret_expand, &string_join, &tmp, data);
			}
			string_join = ft_strjoin2(string_join, *tmp, lexer);
			tmp++;
		}
		ft_free(&string_inp);
		string_inp = ft_readline("> ");
	}
	ft_free (&eof);
	ft_free(&string_inp);
	return (string_join);
}

void	ft_herdoc_2(char **ret_expand, char **string_join,
	char **string_inp, t_data **data)
{
	if (*ret_expand)
	{
		ft_free(string_join);
		*string_join = *ret_expand;
	}
	else
		ft_herdoc_3(string_inp, data);
}

void	ft_herdoc_3(char **string_inp, t_data **data)
{
	if (!(*data)->sign_exp_digit)
	{
		(*string_inp)++;
		while (**string_inp && ft_isalnum(**string_inp)
			&& **string_inp != '$' && !is_whitespace(**string_inp))
			(*string_inp)++;
	}
	else
		(*data)->sign_exp_digit = 0;
}
