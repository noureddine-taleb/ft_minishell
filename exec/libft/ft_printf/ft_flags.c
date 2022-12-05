/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 18:42:33 by ntaleb            #+#    #+#             */
/*   Updated: 2022/10/31 14:47:40 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

void	set_flag(struct s_flags *f, char flag)
{
	if (flag == '-')
	{
		f->zero = 0;
		f->minus = 1;
	}
	else if (flag == '0')
	{
		if (!f->minus)
			f->zero = 1;
	}
	else if (flag == '#')
	{
		f->hash = 1;
	}
	else if (flag == '+')
	{
		f->space = 0;
		f->plus = 1;
	}
	else if (flag == ' ')
	{
		if (!f->plus)
			f->space = 1;
	}
}

int	print_width(struct s_flags *flags)
{
	char	*s;
	int		retval;

	s = ft_itoa(flags->width);
	ft_putstr_fd(s, 1);
	retval = ft_strlen(s);
	free(s);
	return (retval);
}

int	print_dot(struct s_flags *flags)
{
	char	*s;
	int		retval;

	s = ft_itoa(flags->precision);
	ft_putchar_fd('.', 1);
	ft_putstr_fd(s, 1);
	retval = ft_strlen(s) + 1;
	free(s);
	return (retval);
}

int	print_flags(struct s_flags *flags)
{
	int		ret;

	if (flags->hash)
		ft_putchar_fd('#', 1);
	if (flags->space)
		ft_putchar_fd(' ', 1);
	if (flags->plus)
		ft_putchar_fd('+', 1);
	if (flags->minus)
		ft_putchar_fd('-', 1);
	if (flags->zero)
		ft_putchar_fd('0', 1);
	ret = flags->hash + flags->space \
			+ flags->plus + flags->zero + flags->minus;
	if (flags->width)
		ret += print_width(flags);
	if (flags->dot)
		ret += print_dot(flags);
	return (ret);
}

int	isflag(char c)
{
	return (!!ft_strchr("#-0+ ", c));
}
