/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuc_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 01:00:01 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/20 10:06:45 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	if(!ptr)
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

char	*ft_strjoin(char *string, t_lexer *lexer)
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
	new_string[++i] = lexer->c;
	printf("--->%c\n",lexer->c);
	get_next_char(lexer);
	new_string[++i] = '\0';
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (new_string);
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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

// void	ft_putstr(char *str)
// {
// 	char	*null;

// 	null = "(null)";
// 	if (!str)
// 	{
// 		while (*null)
// 			write (1, null++, 1);
// 	}
// 	else
// 	{
// 		while (*str)
// 			write(1, str++, 1);
// 		write (1, "\n", 1);
// 	}
// }

// int	ft_atoi_help(char *str, unsigned int cmp)
// {
// 	while (*str)
// 	{
// 		while (*str && ((*str >= 9 && *str <= 13) || *str == ' '))
// 			str++;
// 		if (*str == '+')
// 			str++;
// 		if (*str && *str >= '0' && *str <= '9')
// 		{
// 			while (*str && *str >= '0' && *str <= '9')
// 			{
// 				cmp = (cmp * 10) + (*str++ - '0');
// 				if (cmp > 4294967295 || (*str == '+'))
// 					return (-1);
// 			}
// 		}
// 		else
// 			return (-1);
// 	}
// 	return (cmp);
// }

// int	ft_atoi(char *str)
// {
// 	unsigned int	cmp;

// 	cmp = 0;
// 	if (ft_strcmp(str, "") == 0 || (ft_strlen(str) == 1 && *str == '+'))
// 		return (-1);
// 	else
// 		return (ft_atoi_help(str, cmp));
// 	return (0);
// }
