/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 02:33:01 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/18 02:51:39 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strjoin(char **string, char c)
{
	int		i;
	char	*new_string;
	char	*str;

	i = -1;
	str = *string;
	new_string = malloc(ft_strlen(*string) + 2);
	if (!new_string)
		return ;
	while (*string && **string)
		new_string[++i] = *((*string)++);
	new_string[++i] = c;
	new_string[++i] = '\0';
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (new_string);
}