/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_free_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:19:06 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/20 17:13:06 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	free_all_data(t_data **data, t_list_token **list_token,
	t_list_cmd **list_cmds, t_lexer **input_commands)
{
	free(*data);
	free_list_token(list_token);
	free_list_cmds(list_cmds);
	free_lexer(input_commands);
}

void	fill_and_execute(t_lexer **input_commands, t_list_token **list_token,
	t_list_cmd **list_cmds, t_data **data)
{
	if (!is_cmd_whitespaces((*input_commands)->command_ling))
	{
		get_token(*input_commands, list_token, data);
		convert_type_word(list_token);
		if (!ft_error(*list_token) && list_token && *list_token)
		{
			if (get_list_cmd(list_token, list_cmds,
					*input_commands, data))
				g_state.exit_status = exec(*list_cmds);
		}
	}
}

void	free_if_ctl_c(t_list_cmd **new_cmd)
{
	if ((*new_cmd)->cmds_args)
	{
		free ((*new_cmd)->cmds_args);
		(*new_cmd)->cmds_args = NULL;
	}
	if ((*new_cmd)->io)
		free_list_inp_out_file(&(*new_cmd)->io);
	free (*new_cmd);
	*new_cmd = NULL;
}
