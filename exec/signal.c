/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:50:59 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/27 11:57:34 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

void	handle_signals(void)
{
	struct sigaction	sa;

	sa = (struct sigaction){.sa_handler = SIG_IGN};

	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal("handle_signals(sigaction)", 1);
}
