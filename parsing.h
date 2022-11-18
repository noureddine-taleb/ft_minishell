/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:45:22 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/18 02:52:37 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<readline/readline.h>
#include<readline/history.h>

typedef struct s_lexer
{
	char	*command_ling;
	int		index;
	char	c;
} t_lexer;

typedef struct s_token
{
	enum
	{
			TOKEN_S_QUOTE,
			TOKEN_D_QUOTE,
			TOKEN_REDI_INPUT,
			TOKEN_REDI_OUTPUT,
			TOKEN_APPAND,
			TOKEN_HERDOC,
			TOKEN_WORD
	} type;
	char *val;
} t_token ;


int		ft_strlen(char *str);
char	*ft_strjoin(char **string, char c);