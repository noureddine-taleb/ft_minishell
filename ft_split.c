/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:48:38 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/18 14:48:52 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_alloc(char **strv, int i)
{
	if (strv[i])
		return (1);
	while (--i >= 0)
		free(strv[i]);
	free(strv);
	return (0);
}

static int	is_string_compose_of(char *s, char c)
{
	if (!*s)
		return (0);
	while (*s && *s == c)
		s++;
	if (!*s)
		return (1);
	return (0);
}

static int	count_words(char *s, char c)
{
	int	count;

	if (is_string_compose_of(s, c))
		return (0);
	count = 1;
	if (!*s)
		return (0);
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s == c)
		{
			while (*s && *s == c)
				s++;
			if (*s)
				count++;
			continue ;
		}
		s++;
	}
	return (count);
}

static char	*get_word(char *s, char c, int *wlen)
{
	char	*start;

	*wlen = 0;
	while (*s && *s == c)
		s++;
	start = s;
	while (*s && *s != c)
	{
		(*wlen)++;
		s++;
	}
	return (start);
}

char	**ft_split(char *str, char c)
{
	char	**words;
	int		i;
	int		wlen;
	int		words_count;

	i = 0;
	if (!str)
		return (NULL);
	words_count = count_words(str, c);
	words = ft_calloc(words_count + 1, sizeof(char *));
	if (!words)
		return (NULL);
	while (i < words_count)
	{
		str = get_word(str, c, &wlen);
		words[i] = malloc(wlen + 1);
		if (!check_alloc(words, i))
			return (NULL);
		ft_strlcpy(words[i], str, wlen + 1);
		str += wlen;
		i++;
	}
	return (words);
}
