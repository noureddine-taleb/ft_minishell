/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:50:59 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/18 22:29:12 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_state.in_heredoc)
		return;
	printf("\n");
	rl_on_new_line(); // behave like we have a new line
	rl_replace_line("", 1); // reset input
	rl_redisplay();   // redisplay the prompt
}

void	handle_signals(void)
{
	struct sigaction	sa;

	sa = (struct sigaction){.sa_handler = sigint_handler,
		.sa_flags = 0};
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal("handle_signals(sigaction)", 1);
}


