/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:59:13 by ntaleb            #+#    #+#             */
/*   Updated: 2021/12/04 17:09:28 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memcpy_b(void *dst, const void *src, size_t n)
{
	void	*p;

	p = dst;
	while (n--)
		*(char *)dst-- = *(char *)src--;
	return (p);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned long	dstp;
	unsigned long	srcp;

	dstp = (unsigned long)dst;
	srcp = (unsigned long)src;
	if (!dst && !src)
		return (dst);
	if (dstp - srcp >= len)
	{
		ft_memcpy(dst, src, len);
	}
	else
	{
		dstp += len - 1;
		srcp += len - 1;
		ft_memcpy_b((void *)dstp, (void *)srcp, len);
	}
	return (dst);
}
