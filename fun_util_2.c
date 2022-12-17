/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_util_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 21:52:38 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/27 10:11:22 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	else
		return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && s2[i] && s1[i] == s2[i])
			i++;
		return (s1[i] - s2[i]);
	}
	else
		return (0);
}

char	*char_convert_string(char c)
{
	char	*string;

	string = malloc(2);
	if (!string)
		return (NULL);
	*string = c;
	*(string + 1) = '\0';
	return (string);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*str;
	char	*ptr;

	if (!str1)
		return (ft_strdup((char *)str2));
	if (!str2)
		return (ft_strdup((char *)str1));
	str = (char *)malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!str)
		return (0);
	ptr = str;
	while (*str1)
		*str++ = *str1++;
	while (*str2)
		*str++ = *str2++;
	*str = '\0';
	return (ptr);
}
