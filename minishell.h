/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:45:22 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/16 01:31:10 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

char	**g_env;

typedef struct s_data
{
	char	*value;
	char	*join_value;
	int		nbr_space;
	char	*new_string;
	int		sign_quote;
	int		sign_token;
	int		sign_d_s_quote;
	int		sign_exp_digit;
	int		sign_find_space;
	int		sign_expand;
	int		sign_expand_2;
	int		sign_for_ambiguous;
	int		nbr_arg;
	int		index;
}	t_data;

typedef struct s_lexer
{
	char	*command_ling;
	int		index;
	char	c;
}	t_lexer;

typedef struct s_token
{
	enum
	{
		TOKEN_REDI_OUTPUT,
		TOKEN_FILE_OUT,
		TOKEN_APPAND,
		TOKEN_FILE_APPAND,
		TOKEN_REDI_INPUT,
		TOKEN_FILE_INP,
		TOKEN_HERDOC,
		TOKEN_FILE_HERDOC,
		TOKEN_WORD,
		TOKEN_PIPE,
	} e_type;
	char	*val;
}	t_token;

typedef struct s_list_token
{
	t_token				*token;
	struct s_list_token	*next;
}	t_list_token;

typedef struct s_list_io_stream
{
	char					*target;
	int						flags;
	struct s_list_io_stream	*next;
}	t_list_io_stream;

typedef struct s_list_cmd
{
	char				**cmds_args;
	t_list_io_stream	*io;
	struct s_list_cmd	*next;
}	t_list_cmd;

int					ft_strlen(char *str);
char				*ft_strdup(char *src);
char				*ft_strjoin2(char *string, char c, t_lexer *lexer);
int					ft_isalpha(int c);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strjoin(char *str1, char *str2);
int					ft_isalnum(int c);
int					ft_isdigit(int c);

char				*char_convert_string(char c);
int					skip_whitespace(t_lexer *lexer);
// int					check_quote(t_list_token *list_token);
int					is_whitespace(char c);
int					is_token(char *lexer);

void				ft_free(char **value);
void				free_lexer(t_lexer **lexer);
void				free_list_token(t_list_token **list_token);
void				free_list_cmds(t_list_cmd **list_cmds);

t_lexer				*init_lexer(char *ling_command);
void				get_next_char(t_lexer *lexer);
t_list_token		*node(t_token **token);
void				add_node(t_list_token **list_token,
						t_list_token *new_token);

t_token				*init_token(int type, char *value);
t_list_token		*get_token(t_lexer *lexer, t_list_token **list_token,
						t_data **data);
t_list_token		*get_token_2(t_list_token **list_token, t_token **token,
						t_lexer *lexer, t_data **data);
void				get_token_3(t_data **data, t_lexer *lexer);
int					get_type_token(char *value, t_data **data);
void				add_token(t_list_token **list_token, t_data **data);
void				add_token_2(t_list_token **list_token, t_data **data);
char				*get_redirection_token(t_lexer *lexer, t_data **data);
char				*s_quote(t_lexer *lexer, t_data **data);
char				*d_quote(t_lexer *lexer, t_data **data,
						t_list_token *list_token);
char				*d_quote_2(t_lexer *lexer, char *string, t_data **data);
char				*d_quote_3(t_lexer *lexer, t_data **data,
						char **string, t_list_token *list_token);
char				*get_pipe_token(t_lexer *lexer, t_data **data);
char				*get_word_token(t_lexer *lexer, t_data **data,
						t_list_token **list_token);
char				*get_word_token_2(t_lexer *lexer, t_data **data,
						char **word, t_list_token **list_token);
char				*get_word_token_3(t_lexer *lexer, t_data **data,
						char **word, t_list_token *tmp);
void				get_word_token_4(t_lexer *lexer, t_data **data, char **word,
						t_list_token **list_token);
void				get_word_token_5(t_lexer *lexer, t_data **data);
char				*get_value(t_lexer *lexer, t_data **data,
						t_list_token **list_token);

char				*ft_expand(char *word, t_lexer *lexer, t_data **data);
char				*ft_expand_2(char *word, t_lexer *lexer);
int					ft_expand_3(t_lexer *lexer, char **str,
						char **ptr, char **env);
char				*expand_digit(t_lexer *lexer, char *word, t_data **data);
char				*expand_digit_2(t_lexer *lexer, char *word);

void				convert_type_word(t_list_token **list_token);
t_list_cmd			*get_list_cmd(t_list_token **list_token,
						t_list_cmd **list_cmds, t_lexer *lexer, t_data **data);
void				add_node_cmd(t_list_cmd **list_cmds, t_list_cmd *new_cmd);
void				init_node(t_list_cmd **new_cmd);
t_list_cmd			*node_list(t_list_token **list_token,
						t_lexer *lexer, t_data **data);
int					nbr_args(t_list_token *list_token);

char				*ft_expand_herdoc(char *string_join,
						char **string_inp, t_data **data);
void				remove_space(char **word);
void				ft_find_space(char **word, t_list_token **list_token,
						t_data **data);
int					nbr_word(char *str);
int					len_list(t_list_token **list_cmd);
int					is_token_2(int type_token);
void				find_space_in_word(char **word, t_data **data);
t_list_token		*end_list(t_list_token **list_token);
void				check_space_in_word(char **word, t_list_token *tmp,
						t_data **data);
int					found_quote(t_lexer *lexer);

int					check_quote_pipe(t_list_token **list_token);
int					check_token(t_list_token **list_token);
int					check_ambiguous(t_list_token **list_token, t_data **data);
int					check_redirection(t_list_token **list_token, t_data **data);
int					is_token_2(int type_token);

char				*ft_herdoc(char *eof, t_data **data, t_lexer *lexer);
void				ft_herdoc_2(char **ret_expand, char **string_join,
						char **string_inp, t_data **data);
void				ft_herdoc_3(char **string_inp, t_data **data);

void				add_node_file(t_list_io_stream **inpt_out_file,
						t_list_io_stream *new_file);
t_list_io_stream	*get_io_file(int flags, char **name_file);
int					is_file(int type_token);
int					find_pipe(t_list_token **list_token);
#endif