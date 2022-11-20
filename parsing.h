/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:45:22 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/20 04:08:20 by kadjane          ###   ########.fr       */
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
			TOKEN_WORD,
			TOKEN_DOLLAR,
			TOKEN_PIPE,
	} type;
	char *val;
} t_token ;


int		ft_strlen(char *str);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *string, char c, t_lexer *lexer);
int		ft_isalpha(int c);
t_lexer	*init_lexer(char *ling_command);
t_token	*get_token(t_lexer *lexer);
char	*char_convert_string(char c);
void	get_next_char(t_lexer *lexer);
void	skip_whitespace(t_lexer *lexer);