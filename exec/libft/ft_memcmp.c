/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:58:56 by ntaleb            #+#    #+#             */
/*   Updated: 2021/12/04 16:06:49 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t len)
{
	while (len)
	{
		if (*(unsigned char *)s1 - *(unsigned char *)s2)
			break ;
		s1++;
		s2++;
		len--;
	}
	if (len == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
