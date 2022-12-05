/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:58:23 by ntaleb            #+#    #+#             */
/*   Updated: 2022/08/12 21:25:09 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

void	handle_flags(const char **fmt, struct s_flags *flags)
{
	ft_bzero(flags, sizeof(*flags));
	while (isflag(**fmt))
	{
		set_flag(flags, **fmt);
		(*fmt)++;
	}
	if (ft_isdigit((**fmt)))
		flags->width = ft_atoi(*fmt);
	while (ft_isdigit((**fmt)))
		(*fmt)++;
	if (**fmt == '.')
	{
		flags->dot = 1;
		(*fmt)++;
		if (ft_isdigit((**fmt)))
			flags->precision = ft_atoi(*fmt);
		while (ft_isdigit((**fmt)))
			(*fmt)++;
	}
	flags->conversion = **fmt;
}

int	ft_do_printf(const char *fmt, va_list ap)
{
	int				ret;
	struct s_flags	flags;

	ret = 0;
	ft_bzero(&flags, sizeof(flags));
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			handle_flags(&fmt, &flags);
			ret += handle_format(&fmt, ap, &flags);
		}
		else
		{
			ft_putchar_fd(*fmt++, 1);
			ret++;
		}
	}
	return (ret);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		retval;

	if (!fmt)
		return (-1);
	va_start(ap, fmt);
	retval = ft_do_printf(fmt, ap);
	va_end(ap);
	return (retval);
}
