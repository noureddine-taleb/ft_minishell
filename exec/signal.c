/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:50:59 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/19 21:42:30 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

/**
 * rl_on_new_line: behave like we have a new line
 * rl_replace_line: reset input
 * rl_redisplay: redisplay the prompt
*/
void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	if (g_state.readline_done)
		return ;
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	(void)sig;
	rl_redisplay();
}

void	handle_signals(void)
{
	struct sigaction	sa;

	sa = (struct sigaction){.sa_handler = sigint_handler,
		.sa_flags = 0};
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal("sigaction", 1);
	sa = (struct sigaction){.sa_handler = sigquit_handler,
		.sa_flags = 0};
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		fatal("sigaction", 1);
}
