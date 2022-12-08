/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:53:43 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/08 18:58:36 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipes(int count, int pipes[][2])
{
	int	i;
	int	ret;

	i = 0;
	while (count--)
	{
		ret = pipe(pipes[i]);
		if (ret < 0)
			die("init_pipes", 1);
		i++;
	}
}

void	get_pipe(int pipes[][2], int pipe[2], int *i)
{
	if ((*i) == 0)
	{
		pipe[0] = -1;
		pipe[1] = pipes[(*i) / 2][!((*i) % 2)];
		(*i)++;
	}
	else
	{
		pipe[0] = pipes[(*i) / 2][!((*i) % 2)];
		(*i)++;
		pipe[1] = pipes[(*i) / 2][!((*i) % 2)];
		(*i)++;
	}
}

void	close_unused_pipes(int pipe[2], int pipes[][2], int len)
{
	int	i;

	i = 0;
	while (len)
	{
		if (pipes[i][0] != pipe[0] && pipes[i][0] != pipe[1])
			if (close(pipes[i][0]))
				die("close_unused_pipes(close)", 4);
		if (pipes[i][1] != pipe[0] && pipes[i][1] != pipe[1])
			if (close(pipes[i][1]))
				die("close_unused_pipes(close)", 4);
		len--;
		i++;
	}
}
