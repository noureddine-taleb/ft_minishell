/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint_hex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:49:13 by ntaleb            #+#    #+#             */
/*   Updated: 2022/08/13 01:02:58 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*utohex(unsigned int i, int upper, struct s_flags *flags)
{
	char	*base;
	char	*str;
	char	*tmp;

	if (upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	str = ft_utoa_base(i, base);
	if (!i)
		flags->hash = 0;
	if (flags->hash)
	{
		tmp = str;
		if (upper)
			str = ft_strjoin("0X", tmp);
		else
			str = ft_strjoin("0x", tmp);
		free(tmp);
	}
	return (str);
}

int	ft_print_uint_hex(unsigned int i, int upper, struct s_flags *flags)
{
	char	*str;

	flags->space = 0;
	flags->plus = 0;
	str = utohex(i, upper, flags);
	if (flags->dot)
	{
		flags->zero = 0;
		if (check_precision(i, flags->precision, &str))
			str = ft_adjust_precision(str, flags->precision, flags);
	}
	return (ft_print_padded_str(str, flags, 1));
}
