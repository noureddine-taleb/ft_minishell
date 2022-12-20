/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:46:38 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/20 18:14:18 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

struct s_state	g_state = {0};

int	ft_error(t_list_token *list_token)
{
	if (check_quote_pipe(&list_token))
	{
		printf("Minishell: syntax error: unexpected end of file\n");
		return (1);
	}
	else if (check_token (&list_token) || check_redirection(&list_token))
	{
		printf("Minishell: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

t_data	*init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		return (NULL);
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

static char	*ft_readline(char *prompt)
{
	char	*ret;

	g_state.readline_done = 0;
	ret = readline(prompt);
	g_state.readline_done = 1;
	return (ret);
}

int	is_cmd_whitespaces(char *str)
{
	if (!str || !ft_strlen(str))
		return (0);
	while (*str && is_whitespace(*str))
		str++;
	return (!*str);
}

int	main(int ac, char **av, char **env)
{
	t_lexer			*input_commands;
	t_list_token	*list_token;
	t_data			*data;
	t_list_cmd		*list_cmds;

	(void) av;
	(void) ac;
	g_state.env = clone_env(env);
	list_token = NULL;
	g_state.exit_status = 0;
	init_shell();
	handle_signals();
	input_commands = init_lexer(ft_readline("Minishell$ "));
	while (input_commands)
	{
		data = init_data(&data);
		if (ft_strcmp(input_commands->command_ling, ""))
		{
			add_history(input_commands->command_ling);
			fill_and_execute(&input_commands, &list_token, &list_cmds, &data);
		}
		free_all_data(&data, &list_token, &list_cmds, &input_commands);
		input_commands = init_lexer(ft_readline("Minishell$ "));
	}
}
