/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:46:38 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/20 09:48:21 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

int main()
{
	t_lexer	*input_commands;
	t_token	*token;
	t_list_token	*list_token;

	token = NULL;
	list_token = NULL;
	while((input_commands = init_lexer(readline("minishell>$ "))) != NULL)
	{
		list_token = get_token(input_commands, token, list_token);
		// while(list_token)
		// {
		// 	printf("type = %d\n",list_token->token->type);
		// 	printf("value = %s\n\n",list_token->token->val);
		// 	list_token = list_token->next;
		// }
		add_history(input_commands->command_ling);
	}

}