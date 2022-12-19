/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 04:40:29 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/19 21:15:36 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	print_cmd_list(t_list_cmd *list_cmds)
{
	struct s_list_io_stream	*io;
	int						j;

	while (list_cmds)
	{
		j = 0;
		while (list_cmds->cmds_args[j])
			printf("\033[90m arg == '%s'\n\033[00m", list_cmds->cmds_args[j++]);
		io = list_cmds->io;
		while (io)
		{
			printf("\033[92m file_flage == %d\n\033[00m", io->flags);
			printf("\033[91m file_name  == %s\n\033[00m", io->target);
			io = io->next;
		}
		printf("------------------------------------------------\n");
		list_cmds = list_cmds->next;
	}
}

t_list_cmd	*get_list_cmd(t_list_token **list_token,
	t_list_cmd **list_cmds, t_lexer *lexer, t_data **data)
{
	t_list_cmd		*new_cmd;
	t_list_token	*tmp;

	tmp = *list_token;
	while (tmp)
	{
		new_cmd = node_list(&tmp, lexer, data, list_cmds);
		if (!list_cmds)
			break ;
		add_node_cmd(list_cmds, new_cmd);
		if (tmp)
			tmp = tmp->next;
	}
	// print_cmd_list(*list_cmds);
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
	t_data **data, t_lexer *lexer, t_list_cmd **list_cmd)
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
		herdoc = ft_herdoc((*list_token)->token->val, data, lexer, list_cmd);
		new_file = get_io_file((*list_token)->token->e_type, &herdoc);
		add_node_file(&((*new_cmd)->io), new_file);
	}
}

t_list_cmd	*node_list(t_list_token **list_token, t_lexer *lexer, t_data **data, t_list_cmd **list_cmd)
{
	int					nbr_arg;
	t_list_cmd			*new_cmd;

	(*data)->index = 0;
	nbr_arg = nbr_args(*list_token);
	new_cmd = ft_calloc(1, sizeof(t_list_cmd));
	if (!new_cmd)
		return (NULL);
	init_node(&new_cmd);
	new_cmd->cmds_args = malloc(sizeof (char **) * (nbr_arg + 1));
	if (!new_cmd->cmds_args)
		return (NULL);
	while (!find_pipe(list_token))
	{
		node_list_2(list_token, &new_cmd, data, lexer, list_cmd);
		(*list_token) = (*list_token)->next;
	}
	new_cmd->cmds_args[(*data)->index] = NULL;
	return (new_cmd);
}
