/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 10:14:36 by ntaleb            #+#    #+#             */
/*   Updated: 2021/12/04 11:46:37 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int n)
{
	int			len;
	long long	ncp;

	ncp = n;
	len = 0;
	if (ncp == 0)
		len++;
	else if (ncp < 0)
	{
		len++;
		ncp *= -1;
	}
	while (ncp > 0)
	{
		len++;
		ncp /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	count;
	char			*s;
	long long		ncp;

	count = num_len(n);
	s = ft_calloc(count + 1, sizeof(char));
	if (!s)
		return (NULL);
	ncp = n;
	if (n < 0)
		ncp *= -1;
	if (ncp == 0)
		s[0] = '0';
	while (ncp)
	{
		s[--count] = ncp % 10 + '0';
		ncp /= 10;
	}
	if (n < 0)
		s[0] = '-';
	return (s);
}
