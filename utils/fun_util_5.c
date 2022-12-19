/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_util_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:16:50 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/18 14:49:36 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	void	*p;

	if (!dst && !src)
		return (dst);
	p = dst;
	while (n--)
		*(char *)dst++ = *(char *)src++;
	return (p);
}

static void	*ft_memcpy_b(void *dst, void *src, size_t n)
{
	void	*p;

	p = dst;
	while (n--)
		*(char *)dst-- = *(char *)src--;
	return (p);
}

void	*ft_memmove(void *dst, void *src, size_t len)
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

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size < dest_len + 1)
		return (size + src_len);
	dest += dest_len;
	size -= dest_len + 1;
	while (size-- && *src)
		*dest++ = *src++;
	*dest = '\0';
	return (dest_len + src_len);
}

void	*ft_memset(void *dest, int v, size_t len)
{
	void	*p;

	p = dest;
	while (len--)
	{
		*(char *)dest++ = v;
	}
	return (p);
}
