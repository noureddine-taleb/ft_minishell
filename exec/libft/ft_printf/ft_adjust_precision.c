/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adjust_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 18:18:18 by ntaleb            #+#    #+#             */
/*   Updated: 2022/08/12 20:53:51 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	to_skip_chars(char *number, struct s_flags *flags)
{
	int	retval;

	retval = 0;
	if (flags->space || flags->plus || number[0] == '-')
	{
		retval++;
	}
	if (flags->hash || flags->conversion == 'p')
	{
		retval += 2;
	}
	return (retval);
}

char	*add_zero_padding(char *old_number, int to_skip, int zeros)
{
	char	*new_number;
	int		i;
	int		new_number_size;

	new_number_size = ft_strlen(old_number) + zeros;
	new_number = malloc(new_number_size + 1);
	ft_strlcpy(new_number, old_number, to_skip + 1);
	i = ft_strlen(new_number);
	while (zeros--)
	{
		new_number[i++] = '0';
	}
	new_number[i] = 0;
	ft_strlcat(new_number, old_number + to_skip, new_number_size + 1);
	return (new_number);
}

char	*ft_adjust_precision(char *number,
			int new_precision, struct s_flags *flags) {
	int		to_skip;
	int		digits;
	int		zeros;
	char	*new_number;

	to_skip = to_skip_chars(number, flags);
	digits = ft_strlen(number + to_skip);
	zeros = 0;
	if (digits < new_precision)
	{
		zeros = new_precision - digits;
		new_number = add_zero_padding(number, to_skip, zeros);
		free(number);
		return (new_number);
	}
	else
	{
		return (number);
	}
}
