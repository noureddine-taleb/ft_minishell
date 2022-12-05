/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 10:04:45 by ntaleb            #+#    #+#             */
/*   Updated: 2021/12/04 16:52:00 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	unsigned int	tlen;
	char			*str;

	if (!s1 || !s2)
		return (NULL);
	tlen = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(tlen);
	if (!str)
		return (NULL);
	*str = 0;
	ft_strlcat(str, s1, tlen);
	ft_strlcat(str, s2, tlen);
	return (str);
}
