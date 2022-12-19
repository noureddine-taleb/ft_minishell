/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_util_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:16:50 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/18 14:38:37 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_ascii_to_int(char c)
{
	return (c - '0');
}

static int	ft_issign(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

static int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi_err(char *str, int *error)
{
	int			sign;
	long long	n;

	sign = 1;
	n = 0;
	while (*str && ft_isspace(*str))
		str++;
	if (*str && ft_issign(*str))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && ft_isnum(*str))
	{
		n = n * 10 + ft_ascii_to_int(*str);
		if (sign == 1 && n > 2147483647)
			return ((*error = 1), -1);
		if (sign == -1 && n > 2147483648)
			return ((*error = 1), 0);
		str++;
	}
	if (*str)
		*error = 1;
	return (sign * n);
}
