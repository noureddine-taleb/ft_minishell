/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 20:40:37 by ntaleb            #+#    #+#             */
/*   Updated: 2022/11/03 18:18:56 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap(char *c1, char *c2)
{
	char	tmp;

	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

char	*reverse(char *s)
{
	int	slen;
	int	i;

	slen = ft_strlen(s);
	i = 0;
	while (i < slen / 2)
	{
		swap(&s[i], &s[slen - 1 - i]);
		i++;
	}
	return (s);
}

char	*ft_utoa_base(unsigned long u, char *base)
{
	int		base_len;
	int		i;
	char	*s;

	s = malloc(64);
	base_len = ft_strlen(base);
	i = 0;
	if (!base || base_len < 2 || !s)
		return (NULL);
	if (u == 0)
	{
		ft_strlcpy(s, base, 2);
		return (s);
	}
	while (u)
	{
		s[i++] = base[u % base_len];
		u /= base_len;
	}
	s[i++] = 0;
	return (reverse(s));
}
