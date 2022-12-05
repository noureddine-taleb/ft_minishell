/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:47:52 by ntaleb            #+#    #+#             */
/*   Updated: 2022/08/13 12:07:17 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(char *str, struct s_flags *flags)
{
	int	free;

	free = 0;
	flags->hash = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->zero = 0;
	if (str && flags->dot && ft_strlen(str) > (size_t)flags->precision)
	{
		str = ft_substr(str, 0, flags->precision);
		free = 1;
	}
	else if (!str)
	{
		str = "(null)";
		if (flags->dot && flags->precision < 6)
		{
			str = ft_substr(str, 0, flags->precision);
			free = 1;
		}
	}
	return (ft_print_padded_str(str, flags, free));
}
