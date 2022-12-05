/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:30:31 by ntaleb            #+#    #+#             */
/*   Updated: 2022/10/31 14:42:38 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

// %%
int	ft_print_percent(struct s_flags *flags)
{
	(void) flags;
	ft_putchar_fd('%', 1);
	return (1);
}
