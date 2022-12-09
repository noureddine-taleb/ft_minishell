/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:46:38 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/09 07:33:58 by kadjane          ###   ########.fr       */
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

// int	check_pipe(t_list_token *list_token)
// {
	
// }

// int	check_redirection(t_list_token *list_token)
// {
	
// }

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	t_lexer			*input_commands;
	t_list_token	*list_token;
	t_data			*data;
	t_list_cmd		*list_cmds;
	// int				i;

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
				free_list_token(&list_token);
			}
			convert_type_word(&list_token);
			list_cmds = get_list_cmd(&list_token, &list_cmds);
			// while (list_cmds)
			// {
			// 	printf("-----> list_cmds == %p\n", list_cmds);
			// 	i = 4;
			// 	while (list_cmds->cmds_args && --i)
			// 		printf("\033[90m arg == %s\n\033[00m", *(list_cmds->cmds_args)++);
			// 	i = 4;
			// 	while (list_cmds->file_to_open && --i)
			// 		printf("\033[91m file_to_open == %s\n\033[00m", *(list_cmds->file_to_open)++);
			// 	printf("\033[92m file_output == %s\n\033[00m", list_cmds->file_output);
			// 	printf("\033[93m outflags == %d\n\033[00m", list_cmds->outflags);
			// 	printf("\033[94m input_source_flag == %d\n\033[00m", list_cmds->input_source_flag);
			// 	list_cmds = list_cmds->next;
			// }
			// char **lines;
			// while (line = getnextline(0))
			// {
			// 	if (strcmp(line, token))
			// 	{
			// 		append(line, lines);
			// 	}
			// 	else
			// 	{
			// 		free(line);
			// 		break;
			// 	}
				
			// }
			// strjoin()
			// printf("@@@@@@@@@%p\n",list_token);
			// while (list_token && list_token->token)
			// {
			// 	printf("\033[92mtype = %d\n", list_token->token->e_type);
			// 	printf("\033[91mvalue = %s\n\n\033[00m", list_token->token->val);
			// 	list_token = list_token->next;
			// }
			// free_lexer(&input_commands);
		}
		free_list_token(&list_token);
		free_list_cmds(&list_cmds);
		input_commands = init_lexer(readline("Minishell$ "));
	}
	// char **tmp;
	// tmp = env;
	// while (*tmp)
	// {
	// 	printf ("%s\n",*tmp);
	// 	tmp++;
	// }
}
