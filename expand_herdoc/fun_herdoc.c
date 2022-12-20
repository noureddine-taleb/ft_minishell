/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_herdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:18:32 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/20 17:29:29 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

static char	*ft_readline(char *prompt, t_data **data)
{
	char	*ret;

	ft_putstr_fd(prompt, 1);
	ret = get_next_line(0, data);
	return (ret);
}

char	*ft_herdoc_4(char **string_join, t_data **data,
	char *string_inp, t_lexer *lexer)
{
	char	*ret_expand;

	ret_expand = NULL;
	while (string_inp && *string_inp)
	{
		if (*string_inp == '$' && !(*data)->sign_d_s_quote)
		{
			ret_expand = ft_expand_herdoc(*string_join, &string_inp, data);
			ft_herdoc_2(&ret_expand, string_join, &string_inp, data);
		}
		*string_join = ft_strjoin2(*string_join, *string_inp, lexer);
		string_inp++;
	}
	return (*string_join);
}

char	*ft_herdoc(char *eof, t_data **data,
	t_lexer *lexer, t_list_cmd **list_cmd)
{
	char	*string_inp;
	char	*string_join;

	string_join = NULL;
	string_inp = ft_readline("> ", data);
	if (string_inp == GNL_INTERRUPT)
		return (printf("\n"), free_list_cmds(list_cmd), GNL_INTERRUPT);
	eof = ft_strjoin(eof, "\n");
	while (string_inp && ft_strcmp(string_inp, eof))
	{
		string_join = ft_herdoc_4(&string_join, data, string_inp, lexer);
		ft_free(&string_inp);
		string_inp = ft_readline("> ", data);
		if (string_inp == GNL_INTERRUPT)
			return (printf("\n"), free_list_cmds(list_cmd),
				ft_free(&string_join), ft_free(&eof), GNL_INTERRUPT);
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
