/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noureddine <noureddine@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:46:34 by noureddine        #+#    #+#             */
/*   Updated: 2021/11/11 09:46:35 by noureddine       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
