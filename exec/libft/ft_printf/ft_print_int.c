/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:03:30 by ntaleb            #+#    #+#             */
/*   Updated: 2022/08/13 01:02:58 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_int(int i, struct s_flags *flags)
{
	char		*str;
	char		*new_str;

	flags->hash = 0;
	str = ft_itoa(i);
	new_str = str;
	if ((flags->space || flags->plus) && i >= 0)
	{
		if (flags->space)
			new_str = ft_strjoin(" ", str);
		else if (flags->plus)
			new_str = ft_strjoin("+", str);
		free(str);
	}
	if (flags->dot)
	{
		flags->zero = 0;
		if (check_precision(i, flags->precision, &new_str))
			new_str = ft_adjust_precision(new_str, flags->precision, flags);
	}
	return (ft_print_padded_str(new_str, flags, 1));
}
