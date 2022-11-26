/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:46:38 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/26 01:10:20 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

int	check_quote(t_list_token *list_token)
{
	while(list_token)
	{
		if(!list_token->token)
		{
			printf("syntax error");
			return (0);
		}
		list_token = list_token->next;
	}
	return (1);
}

int main()
{
	t_lexer	*input_commands;
	t_list_token	*list_token;

	list_token = NULL;
	while((input_commands = init_lexer(readline("Minishell$ "))) != NULL)
	{
		if (ft_strcmp(input_commands->command_ling, "") != 0)
		{
			add_history(input_commands->command_ling);
			list_token = get_token(input_commands, list_token);
			if (!check_quote(list_token))
				return (0);
			while(list_token)
			{
				printf("\033[92mtype = %d\n",list_token->token->type);
				printf("\033[91mvalue = %s\n\n\033[00m",list_token->token->val);
				list_token = list_token->next;
			}
		}
		// while (1)
		// 	;
	}
}