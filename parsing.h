/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:45:22 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/25 19:37:07 by kadjane          ###   ########.fr       */
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
char			*ft_strjoin2(char *string, t_lexer *lexer);
int				ft_isalpha(int c);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strjoin(char *str1, char *str2);
int				ft_isalnum(int c);

char			*char_convert_string(char c);
int				skip_whitespace(t_lexer *lexer);

t_lexer			*init_lexer(char *ling_command);
void			get_next_char(t_lexer *lexer);
t_list_token	*node(t_token **token);
void			add_node(t_list_token **list_token, t_list_token *new_token);

t_token			*init_token(int type, char *value);
t_list_token	*get_token(t_lexer *lexer, t_list_token *list_token);

char	*get_redirection_token(t_lexer *lexer);
char	*s_quote(t_lexer *lexer);
char	*d_quote(t_lexer *lexer);
char	*get_dollar_pipe_token(t_lexer *lexer);
char	*get_word_token(t_lexer *lexer);
int		check_quote(t_list_token *list_token);
int		is_token(char *lexer);