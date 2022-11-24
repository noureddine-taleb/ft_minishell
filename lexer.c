/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:26:21 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/24 21:27:19 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_lexer *init_lexer(char *ling_command)
{
	t_lexer *lexer;
	if (ling_command == 0x0)
		exit(0);
	lexer = malloc(sizeof(t_lexer));
	if(!lexer)
		return (NULL);
	lexer->command_ling = ling_command;
	lexer->index = 0;
	lexer->c = lexer->command_ling[lexer->index];
	return (lexer);
}

void	get_next_char(t_lexer *lexer)
{
	if (lexer->c != '\0' /* && lexer-> index <= ft_strlen(lexer->command_ling)*/)
	{
		lexer->index += 1;
		lexer->c = lexer->command_ling[lexer->index];
	}
}

int	skip_whitespace(t_lexer *lexer)
{
	if (lexer->c != '\0' && (lexer->c == ' ' || lexer->c == '\t'))
	{
		while(lexer->c != '\0' && (lexer->c == ' ' || lexer->c == '\t'))
			get_next_char(lexer);
		return(1);
	}
	return (0);
}
