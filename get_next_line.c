/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:43:41 by kadjane           #+#    #+#             */
/*   Updated: 2022/02/19 17:10:25 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_search(char *ligne)
{
	int	position;

	position = 0;
	if (!ligne)
		return (0);
	while (*ligne)
	{
		position++;
		if (*ligne == '\n')
			return (position);
		ligne++;
	}
	return (0);
}

char	*ft_ligne(char *save, int position, int n)
{
	char	*ligne;
	int		i;

	i = -1;
	if (!*save)
		return (NULL);
	if (n == 0)
		position = ft_strlen(save);
	ligne = malloc(position + 1);
	if (!ligne)
		return (NULL);
	while (++i < position)
		ligne[i] = save[i];
	ligne[i] = '\0';
	return (ligne);
}

char	*ft_save(char *save, int n)
{
	char	*str;
	char	*pstr;
	int		position;
	char	*saveplus;

	if (n == 0)
		return (NULL);
	n = 1;
	position = ft_search(save);
	saveplus = save + position;
	str = malloc(ft_strlen(saveplus) + 1);
	if (!str)
		return (NULL);
	pstr = str;
	while (*saveplus)
		*str++ = *saveplus++;
	*str = '\0';
	return (pstr);
}

char	*ft_get_line(char *ligne, char **save, int n)
{
	char	*tmp;

	tmp = ft_ligne(ligne, ft_search(ligne), n);
	*save = ft_save(ligne, n);
	free(ligne);
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*ligne;
	static char	*save[OPEN_MAX];
	int			n;

	if (fd < 0 || read (fd, NULL, 0) < 0)
		return (NULL);
	if (!save[fd])
		save[fd] = ft_strdup ("");
	ligne = ft_strdup(save[fd]);
	free(save[fd]);
	save[fd] = NULL;
	buff = malloc(256);
	if (!buff)
		return (NULL);
	n = 1;
	while (n && ft_search(ligne) == 0)
	{
		n = read(fd, buff, 255);
		if (n == -1)
			return(NULL);
		*(buff + n) = '\0';
		ligne = ft_strjoin(ligne, buff);
	}
	free(buff);
	return (ft_get_line(ligne, &save[fd], n));
}
