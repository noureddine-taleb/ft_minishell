/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_util_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:16:50 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/18 14:53:25 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	while (n && *s1 && *s2)
	{
		if ((unsigned char)*s1 - (unsigned char)*s2)
			break ;
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return ((char *)0);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	int	retval;

	retval = ft_strlen(src);
	if (size == 0)
		return (retval);
	while (--size > 0 && *src)
		*dst++ = *src++;
	*dst = 0;
	return (retval);
}
