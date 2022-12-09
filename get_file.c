/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 04:40:29 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/09 10:43:18 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	convert_type_word_2(t_list_token **list_token)
{
	if ((*list_token)->token->e_type == TOKEN_REDI_INPUT)
	{
		if ((*list_token)->next->token->e_type == TOKEN_WORD)
			(*list_token)->next->token->e_type = TOKEN_FILE_INP;
	}
	if ((*list_token)->token->e_type == TOKEN_HERDOC)
	{
		if ((*list_token)->next->token->e_type == TOKEN_WORD)
			(*list_token)->next->token->e_type = TOKEN_FILE_HERDOC;
	}
}

void	convert_type_word(t_list_token **list_token)
{
	t_list_token	*tmp;
	
	tmp = *list_token;
	while (tmp)
	{
		if (tmp->token->e_type == TOKEN_REDI_OUTPUT)
		{
			if (tmp->next->token->e_type == TOKEN_WORD)
				tmp->next->token->e_type = TOKEN_FILE_OUT;
		}
		if (tmp->token->e_type == TOKEN_APPAND)
		{
			if (tmp->next->token->e_type == TOKEN_WORD)
				tmp->next->token->e_type = TOKEN_FILE_APPAND;
		}
		convert_type_word_2(&tmp);
		tmp = tmp->next;
	}
}

int	nbr_args(t_list_token *list_token)
{
	int				i;
	t_list_token	*tmp;

	tmp = list_token;
	i = 0;
	while (tmp && tmp->token->e_type != TOKEN_PIPE)
	{
		if(tmp->token->e_type == TOKEN_WORD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	nbr_file_input(t_list_token *list_token)
{
	int				i;
	t_list_token	*tmp;

	tmp = list_token;
	i = 0;
	while (tmp && tmp->token->e_type != TOKEN_PIPE)
	{
		if(tmp->token->e_type == TOKEN_FILE_INP)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_nbr_herdoc(t_list_token *list_token)
{
	int				i;
	t_list_token	*tmp;

	tmp = list_token;
	i = 0;
	while (tmp && tmp->token->e_type != TOKEN_PIPE)
	{
		if(tmp->token->e_type == TOKEN_FILE_HERDOC)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	nbr_file_output(t_list_token *list_token)
{
	int				i;
	t_list_token	*tmp;
	
	i = 0;
	tmp = list_token;
	while (tmp && tmp->token->e_type != TOKEN_PIPE)
	{
		if (tmp->token->e_type == TOKEN_FILE_OUT || tmp->token->e_type == TOKEN_FILE_APPAND)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
int	len_list (t_list_cmd **list_cmd)
{
	t_list_cmd	*tmp;
	int			i;

	i = 0;
	tmp = *list_cmd;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_list_cmd	*get_list_cmd(t_list_token **list_token, t_list_cmd ** list_cmds)
{
	t_list_cmd	*new_cmd;
	t_list_token	*tmp;
	t_list_cmd	*tmp_2;
	int				i;
	int				j;
	
	tmp = *list_token;
	while (tmp)
	{
		new_cmd = node_list(&tmp);
		add_node_cmd(list_cmds, new_cmd);
		if (tmp)
			tmp = tmp->next;
	}
	tmp_2 = *list_cmds;
	while (tmp_2)
	{
		i = 3;
		j = -1;
		while (tmp_2->cmds_args && ++j < 3)
			printf("\033[90m arg == %s\n\033[00m", tmp_2->cmds_args[j]);
		j = -1;
		while (tmp_2->file_to_open && ++j < 3)
			printf("\033[91m file_to_open == %s\n\033[00m", tmp_2->file_to_open[j]);
		j = -1;
		while (tmp_2->file_input && ++j < 3)
			printf("\033[92m file-input == %s\n\033[00m", tmp_2->file_input[j]);
		j = -1;
		while (tmp_2->herdoc && ++j < 3)
			printf("\033[93m herdoc == %s\n\033[00m", tmp_2->herdoc[j]);
		printf("\033[94m file_output == %s\n\033[00m", tmp_2->file_output);
		printf("\033[95m outflags == %d\n\033[00m", tmp_2->outflags);
		printf("\033[96m input_source_flag == %d\n\033[00m", tmp_2->input_source_flag);
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

void	init_node(t_list_cmd **new_cmd)
{
	(*new_cmd)->cmds_args = NULL;
	(*new_cmd)->file_input = NULL;
	(*new_cmd)->file_output = NULL;
	(*new_cmd)->file_to_open = NULL;
	(*new_cmd)->herdoc = NULL;
	(*new_cmd)->outflags = -1;
	(*new_cmd)->input_source_flag = -1;
	(*new_cmd)->next = NULL;
}

t_list_cmd	*node_list(t_list_token **list_token)
{
	int				nbr_arg;
	int				nbr_output;
	int				nbr_input_file;
	int				nbr_herdoc;
	int				index_1;
	int				index_2;
	int				index_3;
	int				index_4;
	t_list_cmd		*new_cmd;

	index_1 = -1;
	index_2 = -1;
	index_3 = -1;
	index_4 = -1;
	nbr_arg = nbr_args(*list_token);
	nbr_output = nbr_file_output(*list_token);
	nbr_input_file = nbr_file_input(*list_token);
	nbr_herdoc = ft_nbr_herdoc(*list_token);
	new_cmd = malloc(sizeof(t_list_cmd));
	if (!new_cmd)
		return (NULL);
	init_node(&new_cmd);
	if (nbr_arg != 0)
	{
		new_cmd->cmds_args = malloc(sizeof (char **) * nbr_arg);
		if (!new_cmd->cmds_args)
			return (NULL);
	}
	if (nbr_input_file != 0)
	{
		new_cmd->file_input = malloc(sizeof (char **) * nbr_input_file);
		if (!new_cmd->file_input)
			return (NULL);
	}
	if (nbr_herdoc != 0)
	{
		new_cmd->herdoc = malloc(sizeof (char **) * nbr_herdoc);
		if (!new_cmd->file_input)
			return (NULL);
	}
	if(nbr_output - 1 > 0)
	{
		new_cmd->file_to_open = malloc(sizeof (char **) * (nbr_output - 1));
		if (!new_cmd->file_to_open)
			return (NULL);
	}
	while (*list_token && (*list_token)->token->e_type != TOKEN_PIPE)
	{
		if ((*list_token)->token->e_type == TOKEN_WORD)
			new_cmd->cmds_args[++index_1] = (*list_token)->token->val;
		else if (((*list_token)->token->e_type == TOKEN_FILE_OUT
				|| (*list_token)->token->e_type == TOKEN_FILE_APPAND) && nbr_output > 1)
		{
			new_cmd->file_to_open[++index_2] = (*list_token)->token->val;
			nbr_output--;
		}
		else if (((*list_token)->token->e_type == TOKEN_FILE_OUT
			|| (*list_token)->token->e_type == TOKEN_FILE_APPAND) && nbr_output == 1)
		{
			new_cmd->file_output = (*list_token)->token->val;
			new_cmd->outflags = (*list_token)->token->e_type ;
		}
		else if ((*list_token)->token->e_type == TOKEN_FILE_INP
				|| (*list_token)->token->e_type == TOKEN_FILE_HERDOC)
		{
			if ((*list_token)->token->e_type == TOKEN_FILE_INP)
				new_cmd->file_input[++index_3] = (*list_token)->token->val;
			else
				new_cmd->herdoc[++index_4] = (*list_token)->token->val;
			new_cmd->input_source_flag = (*list_token)->token->e_type ;
		}
		(*list_token) = (*list_token)->next;
	}
	return (new_cmd);
}