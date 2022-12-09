/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 21:57:59 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/09 08:24:06 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_free(char **value)
{
	if (*value)
	{
		free (*value);
		*value = NULL;
	}
}

void	free_list_token(t_list_token **list_token)
{
	t_list_token	*tmp;
	
	while (*list_token && (*list_token)->next)
	{
		ft_free(&(*list_token)->token->val);
		free((*list_token)->token);
		(*list_token)->token = NULL;
		tmp = *list_token;
		*list_token = (*list_token)->next;
		free (tmp);
		tmp = NULL;
	}
	free(*list_token);
	*list_token = NULL;
}

void	free_list_cmds(t_list_cmd **list_cmds)
{
	t_list_cmd	*tmp;
	
	while (*list_cmds)
	{
		free ((*list_cmds)->cmds_args);
		(*list_cmds)->cmds_args = NULL;
		free ((*list_cmds)->file_input);
		(*list_cmds)->file_input = NULL;
		free ((*list_cmds)->file_to_open);
		(*list_cmds)->file_to_open = NULL;
		free ((*list_cmds)->herdoc);
		(*list_cmds)->herdoc = NULL;
		tmp = *list_cmds;
		*list_cmds = (*list_cmds)->next;
		free (tmp);
	}
	free(*list_cmds);
	*list_cmds= NULL;
}

void	free_lexer(t_lexer **lexer)
{
	ft_free(&(*lexer)->command_ling);
	free(*lexer);
	*lexer = NULL;
}

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
