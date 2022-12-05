/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:11:35 by ntaleb            #+#    #+#             */
/*   Updated: 2021/11/11 10:11:37 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char	*buf;
	size_t	len;

	len = ft_strlen(s) + 1;
	buf = malloc(len);
	if (!buf)
		return (NULL);
	return (ft_memcpy(buf, s, len));
}
