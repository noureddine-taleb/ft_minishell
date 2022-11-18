/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuc_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 01:00:01 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/18 01:00:38 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_putstr(char *str)
{
	char	*null;

	null = "(null)";
	if (!str)
	{
		while (*null)
			write (1, null++, 1);
	}
	else
	{
		while (*str)
			write(1, str++, 1);
		write (1, "\n", 1);
	}
}

int	ft_atoi_help(char *str, unsigned int cmp)
{
	while (*str)
	{
		while (*str && ((*str >= 9 && *str <= 13) || *str == ' '))
			str++;
		if (*str == '+')
			str++;
		if (*str && *str >= '0' && *str <= '9')
		{
			while (*str && *str >= '0' && *str <= '9')
			{
				cmp = (cmp * 10) + (*str++ - '0');
				if (cmp > 4294967295 || (*str == '+'))
					return (-1);
			}
		}
		else
			return (-1);
	}
	return (cmp);
}

int	ft_atoi(char *str)
{
	unsigned int	cmp;

	cmp = 0;
	if (ft_strcmp(str, "") == 0 || (ft_strlen(str) == 1 && *str == '+'))
		return (-1);
	else
		return (ft_atoi_help(str, cmp));
	return (0);
}
