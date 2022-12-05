/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:12:05 by ntaleb            #+#    #+#             */
/*   Updated: 2021/11/11 10:12:07 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
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
