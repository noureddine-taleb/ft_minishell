/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:46:38 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/22 15:36:36 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

int main()
{
	t_lexer	*input_commands;
	t_list_token	*list_token;

	list_token = NULL;
	while((input_commands = init_lexer(readline("Minishell$ "))) != NULL)
	{
		if (ft_strcmp(input_commands->command_ling, "") != 0)
			add_history(input_commands->command_ling);
		list_token = get_token(input_commands, list_token);
		// while(list_token)
		// {
		// 	printf("type = %d\n",list_token->token->type);
		// 	printf("value = %s\n\n",list_token->token->val);
		// 	list_token = list_token->next;
		// }
	}

}