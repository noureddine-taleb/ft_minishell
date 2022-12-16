/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_whitespace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:33:25 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/16 01:34:04 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	skip_whitespace(t_lexer *lexer)
{
	if (lexer->c != '\0' && (lexer->c == ' ' || lexer->c == '\t'))
	{
		while (lexer->c != '\0' && (lexer->c == ' ' || lexer->c == '\t'))
			get_next_char(lexer);
		return (1);
	}
	return (0);
}
