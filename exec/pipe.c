/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:53:43 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/27 11:57:24 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pipes(int count, int pipes[][2])
{
	int	i;
	int	ret;

	i = 0;
	while (count--)
	{
		ret = pipe(pipes[i]);
		if (ret < 0)
			fatal("init_pipes(pipe)", 1);
		i++;
	}
}

void	get_pipe(int pipes[][2], int pipe[2], int *i, int pipe_count)
{
	pipe[0] = -1;
	pipe[1] = -1;
	if (pipe_count == 0)
		return ;
	if ((*i) == 0)
	{
		pipe[1] = pipes[(*i) / 2][!((*i) % 2)];
		(*i)++;
		return ;
	}
	if ((*i) / 2 < pipe_count)
	{
		pipe[0] = pipes[(*i) / 2][!((*i) % 2)];
		(*i)++;
	}
	if ((*i) / 2 < pipe_count)
	{
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
				fatal("close_unused_pipes(close)", 1);
		if (pipes[i][1] != pipe[0] && pipes[i][1] != pipe[1])
			if (close(pipes[i][1]))
				fatal("close_unused_pipes(close)", 1);
		len--;
		i++;
	}
}
