/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:02:30 by ntaleb            #+#    #+#             */
/*   Updated: 2022/10/31 14:41:32 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

int	ft_print_char(char c, struct s_flags *flags)
{
	flags->hash = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->zero = 0;
	return (ft_print_padded_mem(&c, 1, flags, 0));
}
