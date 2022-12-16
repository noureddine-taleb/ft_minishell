/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 21:57:59 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/16 19:52:33 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_free(char **value)
{
	if (value && *value)
	{
		free (*value);
		*value = NULL;
	}
}

void	free_list_token(t_list_token **list_token)
{
	t_list_token	*tmp;

	while (*list_token)
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

void	free_list_inp_out_file(t_list_io_stream **inpt_out_file)
{
	t_list_io_stream	*tmp;

	while (*inpt_out_file)
	{
		if ((*inpt_out_file)->flags == TOKEN_FILE_HERDOC)
			ft_free(&(*inpt_out_file)->target);
		tmp = *inpt_out_file;
		*inpt_out_file = (*inpt_out_file)->next;
		free (tmp);
		tmp = NULL;
	}
}

void	free_list_cmds(t_list_cmd **list_cmds)
{
	t_list_cmd	*tmp;

	while (*list_cmds)
	{
		free ((*list_cmds)->cmds_args);
		(*list_cmds)->cmds_args = NULL;
		free_list_inp_out_file(&(*list_cmds)->io);
		tmp = *list_cmds;
		*list_cmds = (*list_cmds)->next;
		free (tmp);
	}
	free(*list_cmds);
	*list_cmds = NULL;
}

void	free_lexer(t_lexer **lexer)
{
	ft_free(&(*lexer)->command_ling);
	free(*lexer);
	*lexer = NULL;
}
