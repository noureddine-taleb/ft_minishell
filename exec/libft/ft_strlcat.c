/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:11:42 by ntaleb            #+#    #+#             */
/*   Updated: 2021/11/11 10:18:16 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
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
