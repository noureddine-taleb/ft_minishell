/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:26:21 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/18 03:03:42 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_lexer *init_lexer(char *ling_command)
{
	t_lexer *lexer;

	lexer = malloc(sizeof(t_lexer));
	if(!lexer)
		return (NULL);
	lexer->command_ling = ling_command;//lexer->command[lexer->index+ 1]
	lexer->index = 0;
	lexer->c = lexer->command_ling[lexer->index];
	return (lexer);
}
