/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_util_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:16:50 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/16 12:32:45 by ntaleb           ###   ########.fr       */
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


static int	ft_ascii_to_int(char c)
{
	return (c - '0');
}

static int	ft_issign(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

static int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi_err(char *str, int *error)
{
	int			sign;
	long long	n;

	sign = 1;
	n = 0;
	while (*str && ft_isspace(*str))
		str++;
	if (*str && ft_issign(*str))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && ft_isnum(*str))
	{
		n = n * 10 + ft_ascii_to_int(*str);
		if (sign == 1 && n > 2147483647)
			return ((*error = 1), -1);
		if (sign == -1 && n > 2147483648)
			return ((*error = 1), 0);
		str++;
	}
	if (*str)
		*error = 1;
	return (sign * n);
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


static int	check_alloc(char **strv, int i)
{
	if (strv[i])
		return (1);
	while (--i >= 0)
		free(strv[i]);
	free(strv);
	return (0);
}

int	is_string_compose_of(char *s, char c)
{
	if (!*s)
		return (0);
	while (*s && *s == c)
		s++;
	if (!*s)
		return (1);
	return (0);
}

int	count_words(char *s, char c)
{
	int	count;

	if (is_string_compose_of(s, c))
		return (0);
	count = 1;
	if (!*s)
		return (0);
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s == c)
		{
			while (*s && *s == c)
				s++;
			if (*s)
				count++;
			continue ;
		}
		s++;
	}
	return (count);
}

char	*get_word(char *s, char c, int *wlen)
{
	char	*start;

	*wlen = 0;
	while (*s && *s == c)
		s++;
	start = s;
	while (*s && *s != c)
	{
		(*wlen)++;
		s++;
	}
	return (start);
}

char	**ft_split(char *str, char c)
{
	char	**words;
	int		i;
	int		wlen;
	int		words_count;

	i = 0;
	if (!str)
		return (NULL);
	words_count = count_words(str, c);
	words = ft_calloc(words_count + 1, sizeof(char *));
	if (!words)
		return (NULL);
	while (i < words_count)
	{
		str = get_word(str, c, &wlen);
		words[i] = malloc(wlen + 1);
		if (!check_alloc(words, i))
			return (NULL);
		ft_strlcpy(words[i], str, wlen + 1);
		str += wlen;
		i++;
	}
	return (words);
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
