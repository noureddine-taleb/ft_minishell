/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:41:52 by ntaleb            #+#    #+#             */
/*   Updated: 2022/11/03 17:46:31 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_abs(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}