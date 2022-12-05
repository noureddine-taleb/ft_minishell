/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:31:05 by ntaleb            #+#    #+#             */
/*   Updated: 2022/08/13 12:13:39 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ptoa(void *p, struct s_flags *flags)
{
	char	*str;
	char	*tmp;

	if (!p)
		str = ft_strdup("0x0");
	else
	{
		tmp = ft_utoa_base((unsigned long)p, "0123456789abcdef");
		str = ft_strjoin("0x", tmp);
		free(tmp);
		if (flags->space || flags->plus)
		{
			if (flags->space)
				tmp = ft_strjoin(" ", str);
			else
				tmp = ft_strjoin("+", str);
			free(str);
			str = tmp;
		}
	}
	return (str);
}

int	ft_print_ptr(void *p, struct s_flags *flags)
{
	char	*str;

	flags->hash = 0;
	str = ptoa(p, flags);
	if (flags->dot)
	{
		flags->zero = 0;
		str = ft_adjust_precision(str, flags->precision, flags);
	}
	return (ft_print_padded_str(str, flags, 1));
}
