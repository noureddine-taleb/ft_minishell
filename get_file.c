/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 04:40:29 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/16 01:27:34 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_list_cmd	*get_list_cmd(t_list_token **list_token,
	t_list_cmd **list_cmds, t_lexer *lexer, t_data **data)
{
	t_list_cmd		*new_cmd;
	t_list_token	*tmp;
	t_list_cmd		*tmp_2;
	int				j;

	tmp = *list_token;
	while (tmp)
	{
		new_cmd = node_list(&tmp, lexer, data);
		add_node_cmd(list_cmds, new_cmd);
		if (tmp)
			tmp = tmp->next;
	}
	tmp_2 = *list_cmds;
	while (tmp_2)
	{
		j = 0;
		while (tmp_2->cmds_args && tmp_2->cmds_args[j])
			printf("\033[90m arg == '%s'\n\033[00m", tmp_2->cmds_args[j++]);
		while (tmp_2->io)
		{
			printf("\033[92m file_flage == %d\n\033[00m", tmp_2->io->flags);
			printf("\033[91m file_name  == {%s}\n\033[00m", tmp_2->io->target);
			tmp_2->io = tmp_2->io->next;
		}
		printf("------------------------------------------------\n");
		tmp_2 = tmp_2->next;
	}
	return (*list_cmds);
}

void	add_node_cmd(t_list_cmd **list_cmds, t_list_cmd *new_cmd)
{
	t_list_cmd	*tmp;

	tmp = *list_cmds;
	if (!(*list_cmds))
		*list_cmds = new_cmd;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		(tmp)->next = new_cmd;
	}
}

void	node_list_2(t_list_token **list_token, t_list_cmd **new_cmd,
	t_data **data, t_lexer *lexer)
{
	char				*herdoc;
	t_list_io_stream	*new_file;

	herdoc = NULL;
	if (*list_token && (*list_token)->token->e_type == TOKEN_WORD)
		(*new_cmd)->cmds_args[(*data)->index++] = (*list_token)->token->val;
	else if (*list_token && is_file((*list_token)->token->e_type))
	{
		new_file = get_io_file((*list_token)->token->e_type,
				&(*list_token)->token->val);
		add_node_file(&((*new_cmd)->io), new_file);
	}
	else if (*list_token && (*list_token)->token
		&& (*list_token)->token->e_type == TOKEN_FILE_HERDOC)
	{
		herdoc = ft_herdoc((*list_token)->token->val, data, lexer);
		new_file = get_io_file((*list_token)->token->e_type, &herdoc);
		add_node_file(&((*new_cmd)->io), new_file);
	}
}

t_list_cmd	*node_list(t_list_token **list_token, t_lexer *lexer, t_data **data)
{
	int					nbr_arg;
	t_list_cmd			*new_cmd;

	(*data)->index = 0;
	nbr_arg = nbr_args(*list_token);
	new_cmd = malloc(sizeof(t_list_cmd));
	if (!new_cmd)
		return (NULL);
	init_node(&new_cmd);
	if (nbr_arg)
	{
		new_cmd->cmds_args = malloc(sizeof (char **) * (nbr_arg + 1));
		if (!new_cmd->cmds_args)
			return (NULL);
	}
	while (!find_pipe(list_token))
	{
		node_list_2(list_token, &new_cmd, data, lexer);
		(*list_token) = (*list_token)->next;
	}
	if (new_cmd->cmds_args)
		new_cmd->cmds_args[(*data)->index] = NULL;
	return (new_cmd);
}
