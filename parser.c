/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:46:38 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/20 04:11:32 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

int main()
{
	t_token	*token;
	t_lexer	*input_commands;

	while((input_commands = init_lexer(readline("minishell>$ "))) != NULL)
	{
		token = get_token(input_commands);
		add_history(input_commands->command_ling);
	}

}