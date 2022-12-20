/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:17:33 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/20 15:17:44 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_entry_location(char *addr, char **arr)
{
	while (*arr)
	{
		if (*arr == addr)
			return (arr);
		arr++;
	}
	return (NULL);
}
