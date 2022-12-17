/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:46:38 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/17 16:01:42 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

struct s_state g_state = {0};

int	ft_error(t_list_token *list_token, t_data **data)
{
	int	i;

	i = 0;
	if (check_quote_pipe(&list_token))
	{
		printf("Minishell: syntax error: unexpected end of file\n");
		return (1);
	}
	else if (check_token (&list_token) || check_redirection(&list_token, data))
	{
		printf("Minishell: syntax error near unexpected token\n");
		return (1);
	}
	else if (check_ambiguous(&list_token, data))
	{
		printf("Minishell: ambiguous redirect\n");
		return (1);
	}
	return (0);
}

t_data	*init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	(*data)->sign_d_s_quote = 0;
	(*data)->sign_quote = 0;
	(*data)->sign_find_space = 0;
	(*data)->sign_expand = 0;
	(*data)->sign_token = 0;
	(*data)->sign_expand_2 = 0;
	(*data)->sign_for_ambiguous = 0;
	(*data)->join_value = NULL;
	(*data)->value = NULL;
	return (*data);
}

int	main(int ac, char **av, char **env)
{
	t_lexer			*input_commands;
	t_list_token	*list_token;
	t_data			*data;
	t_list_cmd		*list_cmds;

	(void) av;
	(void) ac;
	g_state.env = env;
	list_token = NULL;
	g_state.exit_status = 0;
	input_commands = init_lexer(readline("Minishell$ "));
	while (input_commands)
	{
		data = init_data(&data);
		data->sign_for_ambiguous = 0;
		if (ft_strcmp(input_commands->command_ling, "") != 0)
		{
			add_history(input_commands->command_ling);
			get_token(input_commands, &list_token, &data);
			convert_type_word(&list_token);
			if (!ft_error(list_token, &data))
			{

				list_cmds = get_list_cmd(&list_token, &list_cmds,
						input_commands, &data);
				g_state.exit_status = exec(list_cmds);
			}
		}
		free(data);
		free_list_token(&list_token);
		free_list_cmds(&list_cmds);
		free_lexer(&input_commands);
		input_commands = init_lexer(readline("Minishell$ "));
	}
}
