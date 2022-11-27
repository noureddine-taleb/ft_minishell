/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:26:21 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/27 04:10:24 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*init_lexer(char *ling_command)
{
	t_lexer	*lexer;

	if (!ling_command)
		exit(0);
	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->command_ling = ling_command;
	lexer->index = 0;
	lexer->c = lexer->command_ling[lexer->index];
	return (lexer);
}

void	get_next_char(t_lexer *lexer)
{
	if (lexer->c != '\0')
	{
		lexer->index += 1;
		lexer->c = lexer->command_ling[lexer->index];
	}
}
