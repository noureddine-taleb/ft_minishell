/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 04:40:29 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/06 08:04:08 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// t_list_cmd	*node_cmd(char **cmd_arg, int *fd_inpt, int fd_out)
// {
// 	t_list_cmd	*new_cmd;
	
// 	new_cmd = malloc(sizeof(t_list_cmd));
// 	if (!new_cmd)
// 		return(NULL);
	
// }

void	convert_type_word_2(t_list_token **list_token)
{
	if ((*list_token)->token->e_type == TOKEN_REDI_INPUT)
	{
		if ((*list_token)->next->token->e_type == TOKEN_WORD)
			(*list_token)->next->token->e_type = TOKEN_FIlE_INP;
	}
	if ((*list_token)->token->e_type == TOKEN_HERDOC)
	{
		if ((*list_token)->next->token->e_type == TOKEN_WORD)
			(*list_token)->next->token->e_type = TOKEN_FIlE_HERDOC;
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
				tmp->next->token->e_type = TOKEN_FIlE_OUT;
		}
		if (tmp->token->e_type == TOKEN_APPAND)
		{
			if (tmp->next->token->e_type == TOKEN_WORD)
				tmp->next->token->e_type = TOKEN_FIlE_APPAND;
		}
		convert_type_word_2(&tmp);
		tmp = tmp->next;
	}
}

int	nbr_arg(t_list_token **list_token)
{
	int		i;
	t_list_token	*tmp;

	tmp = *list_token;
	i = 0;
	while (tmp && tmp->token->e_type != TOKEN_PIPE)
	{
		if(tmp->token->e_type == TOKEN_WORD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}


t_list_cmd	*get_list_cmd(t_list_token *list_token, t_list_cmd ** list_cmds)
{
	char	**cmd_arg;
	int		fd_input;
	int		fd_output;
	int		i;

	i = 0;
	while (list_token)
	{
		while (list_token->token->e_type != TOKEN_PIPE)
		{
			i = nbr_arg(&list_token);
			cmd_arg = malloc(sizeof (char **) * i);
			while (list_token->token->e_type == TOKEN_WORD)
			{
				*cmd_arg++ = ft_strdup(list_token->token->val);
				list_token = list_token->next;
			}
			if(list_token->token->e_type != TOKEN_PIPE && )
			{
				
				get_file();
		}
	}
}