/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_precision_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 00:54:46 by ntaleb            #+#    #+#             */
/*   Updated: 2022/08/13 01:09:51 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_precision(unsigned int i, int precision, char **s)
{
	if (!i && !precision)
	{
		free(*s);
		*s = ft_strdup("");
		return (0);
	}
	return (1);
}
