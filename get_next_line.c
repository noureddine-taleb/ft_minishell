/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:43:41 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/20 14:54:02 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_search(char *ling)
{
	int	position;

	position = 0;
	if (!ling)
		return (0);
	while (*ling)
	{
		position++;
		if (*ling == '\n')
			return (position);
		ling++;
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
	ft_free(&ligne);
	return (tmp);
}

char	*get_next_line(int fd, t_data **d)
{
	static char	*save[OPEN_MAX];
	char		*tmp;

	if (fd < 0 || read (fd, NULL, 0) < 0)
		return (NULL);
	if (!save[fd])
		save[fd] = ft_strdup ("");
	(*d)->ling = ft_strdup(save[fd]);
	ft_free(&save[fd]);
	(*d)->buff = malloc(256);
	if (!(*d)->buff)
		return (NULL);
	while (!ft_search((*d)->ling))
	{
		(*d)->n = read(fd, (*d)->buff, 255);
		if (!(*d)->n && !ft_strlen((*d)->ling))
			break ;
		if ((*d)->n == -1)
			return (ft_free(&(*d)->ling), ft_free(&(*d)->buff), GNL_INTERRUPT);
		*((*d)->buff + (*d)->n) = '\0';
		tmp = (*d)->ling;
		(*d)->ling = ft_strjoin((*d)->ling, (*d)->buff);
		ft_free (&tmp);
	}
	return (ft_free(&(*d)->buff), ft_get_line((*d)->ling, &save[fd], (*d)->n));
}
