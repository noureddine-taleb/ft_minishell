/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:46:38 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/29 10:53:29 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_quote(t_list_token *list_token)
{
	while (list_token)
	{
		if (!list_token->token)
			return (1);
		list_token = list_token->next;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	t_lexer			*input_commands;
	t_list_token	*list_token;
	t_data			*data;

	list_token = NULL;
	data = malloc(sizeof(t_data));
	data->env = env;
	input_commands = init_lexer(readline("Minishell$ "));
	while (input_commands)
	{
		if (ft_strcmp(input_commands->command_ling, "") != 0)
		{
			add_history(input_commands->command_ling);
			list_token = get_token(input_commands, list_token, &data);
			if (check_quote(list_token))
			{
				printf("syntax error\n");
				free_list(&list_token);
			}
			while (list_token && list_token->token)
			{
				printf("\033[92mtype = %d\n", list_token->token->e_type);
				printf("\033[91mvalue = %s\n\n\033[00m", list_token->token->val);
				list_token = list_token->next;
			}
			free_lexer(&input_commands);
		}
		free_list(&list_token);
		// while (1)
		// 	;
		input_commands = init_lexer(readline("Minishell$ "));
	}
	// char **tmp;
	
	// tmp = envp;
	// while (*tmp)
	// {
	// 	printf ("---%s\n",*tmp);
	// 	tmp++;
	// }
}
