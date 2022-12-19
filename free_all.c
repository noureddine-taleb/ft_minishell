/* ************************************************************************************************ */
/*                                                                                                  */
/*                                                        :::   ::::::::   ::::::::  :::::::::::    */
/*   free_all.c                                        :+:+:  :+:    :+: :+:    :+: :+:     :+:     */
/*                                                      +:+         +:+        +:+        +:+       */
/*   By: kadjane <kadjane@student.1337.ma>             +#+      +#++:      +#++:        +#+         */
/*                                                    +#+         +#+        +#+      +#+           */
/*   Created: 2022/12/19 23:35:01 by kadjane         #+#  #+#    #+# #+#    #+#     #+#             */
/*   Updated: 2022/12/19 23:35:01 by kadjane      ####### ########   ########      ###.ma           */
/*                                                                                                  */
/* ************************************************************************************************ */

#include"minishell.h"

void free_all_data(t_data **data, t_list_token **list_token,
	t_list_cmd **list_cmds, t_lexer **input_commands)
{
	free(*data);
	free_list_token(list_token);
	free_list_cmds(list_cmds);
	free_lexer(input_commands);
}
