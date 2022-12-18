/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_util_6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:49:21 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/18 14:49:40 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t len)
{
	ft_memset(s, 0, len);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*buf;

	buf = malloc(count * size);
	if (!buf)
		return (NULL);
	ft_bzero(buf, count * size);
	return (buf);
}
