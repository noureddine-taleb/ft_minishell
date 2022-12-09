/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_util_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 21:36:50 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/07 05:01:47 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *p, int v, size_t c)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)p;
	i = -1;
	while (++i < c)
		*(ptr++) = (unsigned char)v;
	return (p);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void	*ft_calloc(size_t cnt, size_t size)
{
	char	*p;

	p = (char *)malloc(cnt * size);
	if (!p)
		return (0);
	ft_bzero(p, cnt * size);
	return (p);
}
