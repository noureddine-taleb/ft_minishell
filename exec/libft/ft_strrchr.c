/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:13:00 by ntaleb            #+#    #+#             */
/*   Updated: 2021/12/04 16:15:13 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	char	*found;

	found = (char *)0;
	while (*s)
	{
		if (*s == (char)c)
			found = s;
		s++;
	}
	if (!found && c == 0)
		found = s;
	return (found);
}
