/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 21:57:59 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/26 22:21:16 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_free(char **value)
{
	free (*value);
	*value = NULL;
}

void	free_list(t_list_token **list_token)
{
	while((*list_token)->next)
	{
		ft_free(&(*list_token)->token->val);
		free ((*list_token)->token);
		(*list_token)->token = NULL;
		*list_token = (*list_token)->next;
	}
	*list_token = NULL;
}

int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13 )|| c == ' ')
		return (1);
	return (0);
}

int	is_token(char *lexer)
{
	 
	if (!ft_strcmp(lexer,">") || !ft_strcmp(lexer,">>")
		|| !ft_strcmp(lexer,"<") || !ft_strcmp(lexer,"<<")
		|| !ft_strcmp(lexer,"$") || !ft_strcmp(lexer,"|")
		|| !ft_strcmp(lexer,"'") || !ft_strcmp(lexer,"\""))
			return (1);
	return (0);
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