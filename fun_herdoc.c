/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_herdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:18:32 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/16 13:40:31 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char *ft_readline(char *prompt)
{
	char *ret;

	ret = readline(prompt);
	ret = ft_strjoin(ret, "\n");
	return (ret);
}

char	*ft_herdoc(char *eof, t_data **data, t_lexer *lexer)
{
	char	*string_inp;
	char	*string_join;
	char	*ret_expand ;

	ret_expand = NULL;
	string_join = NULL;
	string_inp = ft_readline("> ");
	eof = ft_strjoin(eof, "\n");
	while (string_inp && ft_strcmp(string_inp, eof))
	{
		while (string_inp && *string_inp)
		{
			if (*string_inp == '$' && !(*data)->sign_d_s_quote)
			{
				ret_expand = ft_expand_herdoc(string_join, &string_inp, data);
				ft_herdoc_2(&ret_expand, &string_join, &string_inp, data);
			}
			string_join = ft_strjoin2(string_join, *string_inp, lexer);
			string_inp++;
		}
		string_inp = ft_readline("> ");
	}
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
	char	*str;

	if (!(*data)->sign_exp_digit)
	{
		(*string_inp)++;
		str = char_convert_string(**string_inp);
		while (**string_inp && ft_isalnum(**string_inp)
			&& **string_inp != '$' && !is_whitespace(**string_inp))
		{
			(*string_inp)++;
			ft_free(&str);
			str = char_convert_string(**string_inp);
		}
	}
	else
		(*data)->sign_exp_digit = 0;
}
