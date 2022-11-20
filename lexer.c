/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:26:21 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/20 00:58:08 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_lexer *init_lexer(char *ling_command)
{
	t_lexer *lexer;

	lexer = malloc(sizeof(t_lexer));
	if(!lexer)
		return (NULL);
	lexer->command_ling = ft_strdup(ling_command);
	lexer->index = 0;
	lexer->c = lexer->command_ling[lexer->index];
	return (lexer);
}

void	get_next_char(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer-> index < ft_strlen(lexer->command_ling))
	{
		lexer->index += 1;
		lexer->c = lexer->command_ling[lexer->index];
	}
}

void	skip_whitespace(t_lexer *lexer)
{
	while((lexer->c != '\0' && lexer->index < ft_strlen(lexer->command_ling))
			&& (lexer->c == ' ' || lexer->c == '\t'))
				get_next_char(lexer);
}
