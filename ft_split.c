/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:14:09 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/07 05:02:12 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

int	len_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s && *s && *s++ != c)
		i++;
	return (i);
}

char	*allocat(char const *s, char **tab_str, char c, int i)
{
	int	j;

	*(tab_str + i) = (char *)ft_calloc(len_word(s, c) + 1, sizeof(char));
	if (!tab_str)
	{
		j = 0;
		while (j++ < i)
			free(*(tab_str + j));
		free(tab_str);
		return (0);
	}
	return (*(tab_str + i));
}

char	**rempl_tab(char const *s, char **tab_str, char c)
{
	int	l;
	int	k;
	int	i;
	int	m;

	i = -1;
	k = nbr_word(s, c);
	while (*s && ++i < k)
	{
		while (*s == c)
			s++;
		allocat(s, tab_str, c, i);
		if (!tab_str)
			return (0);
		m = len_word(s, c);
		l = -1;
		while (*s != c && ++l < m)
			tab_str[i][l] = *s++;
	}
	return (tab_str);
}

char	**ft_split(char const *s, char c)
{
	char	**tab_str;

	if (!s)
		return (0);
	tab_str = (char **)ft_calloc((nbr_word(s, c) + 1), sizeof(char *));
	if (!tab_str)
		return (0);
	rempl_tab(s, tab_str, c);
	return (tab_str);
}
