/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:45:22 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/20 10:07:22 by kadjane          ###   ########.fr       */
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

typedef struct s_list_token
{
	t_token				*token;
	struct s_list_token	*next;
} t_list_token;

int				ft_strlen(char *str);
char			*ft_strdup(char *src);
char			*ft_strjoin(char *string, t_lexer *lexer);
int				ft_isalpha(int c);
t_lexer			*init_lexer(char *ling_command);
t_list_token	*get_token(t_lexer *lexer,t_token *token, t_list_token *list_token);
char			*char_convert_string(char c);
void			get_next_char(t_lexer *lexer);
void			skip_whitespace(t_lexer *lexer);
t_list_token	*node(t_token **token);
void			add_node(t_list_token **list_token, t_list_token *new_token);
t_token			*get_quote(t_lexer *lexer, t_token *token);
t_token			*get_dollar_pipe_token(t_lexer *lexer, t_token *token);
int				ft_strcmp(char *s1, char *s2);