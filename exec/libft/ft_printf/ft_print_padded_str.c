/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_padded_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:09:08 by ntaleb            #+#    #+#             */
/*   Updated: 2022/08/12 20:47:44 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_padded_str(char *str,
				struct s_flags *flags, int _free) {
	return (ft_print_padded_mem(str, ft_strlen(str), flags, _free));
}

int	ft_print_prefix(char *src, struct s_flags *flags)
{
	int	retval;

	retval = 0;
	if (src[0] == '-' || flags->space || flags->plus)
	{
		ft_putchar_fd(src[0], 1);
		retval++;
	}
	if (
		flags->conversion == 'p'
		|| (flags->conversion == 'x' && flags->hash)
	)
	{
		ft_putstr_fd("0x", 1);
		retval += 2;
	}
	if (flags->conversion == 'X' && flags->hash)
	{
		ft_putstr_fd("0X", 1);
		retval += 2;
	}
	return (retval);
}

int	handle_front(int blank, struct s_flags *flags, char *src)
{
	int	offset;

	offset = 0;
	if (flags->zero)
	{
		offset = ft_print_prefix(src, flags);
		while (blank--)
			ft_putchar_fd('0', 1);
	}
	else if (!flags->zero && !flags->minus)
		while (blank--)
			ft_putchar_fd(' ', 1);
	return (offset);
}

void	handle_back(int blank, struct s_flags *flags)
{
	if (flags->minus)
		while (blank--)
			ft_putchar_fd(' ', 1);
}

int	ft_print_padded_mem(char *src, int len, struct s_flags *flags, int _free)
{
	int	retval;
	int	offset;
	int	remaining;

	retval = len;
	offset = 0;
	if (flags->width > len)
	{
		remaining = flags->width - len;
		retval = flags->width;
		offset = handle_front(remaining, flags, src);
		ft_putmem_fd(src + offset, len - offset, 1);
		handle_back(remaining, flags);
	}
	else
		ft_putmem_fd(src, len, 1);
	if (_free)
		free(src);
	return (retval);
}
