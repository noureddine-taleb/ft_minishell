/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuc_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 01:00:01 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/14 14:40:43 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && *str)
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_strdup(char *src)
{
	int		len;
	int		i;
	char	*ptr;
	char	*string;

	i = -1;
	if (!src)
		return (NULL);
	len = ft_strlen(src) + 1;
	ptr = (char *)malloc(len);
	if (!ptr)
		return (NULL);
	string = ptr;
	while (src[++i])
		*ptr++ = src[i];
	*ptr = '\0';
	return (string);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

char	*ft_strjoin2(char *string, char c, t_lexer *lexer)
{
	int		i;
	char	*new_string;
	char	*str;

	i = -1;
	str = string;
	new_string = malloc(ft_strlen(string) + 2);
	if (!new_string)
		return (NULL);
	while (string && *string)
		new_string[++i] = *string++;
	new_string[++i] = c;
	new_string[++i] = '\0';
	get_next_char(lexer);
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (new_string);
}
