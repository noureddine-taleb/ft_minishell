/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 22:04:40 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/26 22:21:59 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	get_type_token(char *value)
{
	if (!value)
		return (-1);
	if (!ft_strcmp(value,">"))
		return (TOKEN_REDI_INPUT);
	if (!ft_strcmp(value,"<"))
		return (TOKEN_REDI_OUTPUT);
	if (!ft_strcmp(value,"<<"))
		return (TOKEN_HERDOC);
	if (!ft_strcmp(value,">>"))
		return (TOKEN_APPAND);
	if (!ft_strcmp(value,"|"))
		return (TOKEN_PIPE);
	if (!ft_strcmp(value,"$"))
		return (TOKEN_DOLLAR);
	return(TOKEN_WORD);
}

void	add_token(t_list_token **list_token, char **join_value, char **value)
{
	t_token		*token;
	int			type_token;
	
	if (*join_value)
	{
		type_token = get_type_token(*join_value);
		token = init_token(type_token, *join_value);
		ft_free(join_value);
		add_node(list_token,node(&token));
	}
	type_token = get_type_token(*value);
	token = init_token(type_token, *value);
	ft_free(value);
	add_node(list_token,node(&token));
}

void	add_token_2(t_list_token **list_token, int *nbr_space, char **join_value, char **value)
{
	t_token	*token;
	int		type_token;

	*nbr_space = 0;
	type_token = get_type_token(*join_value);
	token = init_token(type_token, *join_value);
	ft_free (join_value);
	ft_free(value);
	add_node(list_token,node(&token));
}