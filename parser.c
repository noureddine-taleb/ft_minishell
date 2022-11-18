/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:46:38 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/16 19:10:02 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

int main()
{
	t_lexer	*input_commands;

	input_commands = malloc(sizeof(t_lexer));
	if (!input_commands)
		return (0);
	while((input_commands->command_ling = readline("minishell>$ ")) != NULL)
	{
		add_history(input_commands->command_ling);
	}

}