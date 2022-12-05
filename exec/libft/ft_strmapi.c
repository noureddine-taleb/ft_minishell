/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmapi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 10:07:58 by ntaleb            #+#    #+#             */
/*   Updated: 2021/12/04 16:47:15 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	unsigned int	i;
	char			*new;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	new[len] = 0;
	while (s[i])
	{
		new[i] = f(i, s[i]);
		i++;
	}
	return (new);
}
