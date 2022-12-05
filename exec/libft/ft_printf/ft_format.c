/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 20:56:24 by ntaleb            #+#    #+#             */
/*   Updated: 2022/08/12 20:58:33 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>

int	is_conversion(char c)
{
	if (ft_strchr("%csiduxXp", c))
		return (1);
	return (0);
}

int	invoke_conversion(char c, va_list ap, struct s_flags *flags)
{
	if ('%' == c)
		return (ft_print_percent(flags));
	else if ('c' == c)
		return (ft_print_char(va_arg(ap, int), flags));
	else if ('s' == c)
		return (ft_print_str(va_arg(ap, char *), flags));
	else if ('i' == c || 'd' == c)
		return (ft_print_int(va_arg(ap, int), flags));
	else if ('u' == c)
		return (ft_print_uint(va_arg(ap, unsigned int), flags));
	else if ('x' == c || 'X' == c)
		return (ft_print_uint_hex(va_arg(ap, unsigned int), c == 'X', flags));
	else if ('p' == c)
		return (ft_print_ptr(va_arg(ap, void *), flags));
	return (0);
}

int	handle_format(const char **fmt, va_list ap, struct s_flags *flags)
{
	int		ret;

	if (is_conversion(**fmt))
	{
		ret = invoke_conversion(**fmt, ap, flags);
		(*fmt)++;
	}
	else
	{
		ft_putchar_fd('%', 1);
		ret = 1;
	}
	return (ret);
}
