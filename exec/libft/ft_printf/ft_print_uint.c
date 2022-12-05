/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:57:50 by ntaleb            #+#    #+#             */
/*   Updated: 2022/08/13 01:04:22 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_uint(unsigned int i, struct s_flags *flags)
{
	char	*str;

	str = ft_utoa_base(i, "0123456789");
	flags->plus = 0;
	flags->space = 0;
	flags->hash = 0;
	if (flags->dot)
	{
		flags->zero = 0;
		if (check_precision(i, flags->precision, &str))
			str = ft_adjust_precision(str, flags->precision, flags);
	}
	return (ft_print_padded_str(str, flags, 1));
}
