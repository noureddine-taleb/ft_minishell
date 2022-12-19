/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_util_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 21:36:50 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/14 10:43:36 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_space(char **word)
{
	char	*tmp;
	t_lexer	*lexer;
	char	*word_without_space;

	tmp = *word;
	lexer = NULL;
	word_without_space = NULL;
	while (tmp && *tmp && is_whitespace(*tmp))
		tmp++;
	while (tmp && *tmp && !is_whitespace(*tmp))
		word_without_space = ft_strjoin2(word_without_space, *tmp++, lexer);
	ft_free(word);
	*word = word_without_space;
}
