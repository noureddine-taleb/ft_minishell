/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:03:16 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/19 17:42:19 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/**
 * this function tells you if an arg contain a flag
 * like if the flag is "n" arg like "-n", "-nnnn+"
 * are all acceptable
*/
int	arg_equal_flag(char *arg, char flag)
{
	if (!arg || ft_strlen(arg) < 2 || arg[0] != '-')
		return (0);
	arg++;
	while (*arg == flag)
		arg++;
	if (!*arg)
		return (1);
	return (0);
}
