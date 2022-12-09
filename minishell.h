/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:45:22 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/09 11:43:16 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char	*value;
	char	*join_value;
	int		nbr_space;
	char	**env;
	char	*ptr;
	char	*str;
	char	*found;
	char	*new_string;
	int		sign_d_quote;
	int		sign_exp_digit;
	// int		nbr_arg;
	// int		nbr_input_file;
	// int		nbr_file_to_open;
	// int		nbr_herdoc;
}	t_data;

typedef struct s_lexer
{
	char	*command_ling;
	int		index;
	char	c;
}	t_lexer;

char	**g_env;

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

struct cmd {
};

typedef struct s_list_cmd
{
	char	**cmds_args;
	char	**file_input;
	char	**file_to_open;
	char	**herdoc;
	char	*file_output;
	int		input_source_flag; // file=/heredoc=/nothing=0
	int		outflags; // is append ?
	struct s_list_cmd	*next;
	
}	t_list_cmd;

int				ft_strlen(char *str);
char			*ft_strdup(char *src);
char			*ft_strjoin2(char *string, char c, t_lexer *lexer);
int				ft_isalpha(int c);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strjoin(char *str1, char *str2);
int				ft_isalnum(int c);
int				ft_isdigit(int c);
char			**ft_split(char const *s, char c);
void			*ft_calloc(size_t cnt, size_t size);

char			*char_convert_string(char c);
int				skip_whitespace(t_lexer *lexer);
int				check_quote(t_list_token *list_token);
int				is_whitespace(char c);
int				is_token(char *lexer);

void			ft_free(char **value);
void			free_lexer(t_lexer **lexer);
void			free_list_token(t_list_token **list_token);
void			free_list_cmds(t_list_cmd **list_cmds);

t_lexer			*init_lexer(char *ling_command);
void			get_next_char(t_lexer *lexer);
t_list_token	*node(t_token **token);
void			add_node(t_list_token **list_token, t_list_token *new_token);

t_token			*init_token(int type, char *value);
t_list_token	*get_token(t_lexer *lexer, t_list_token *list_token,
					t_data **data);
t_list_token	*get_token_2(t_list_token *list_token, t_token **token,
					t_lexer *lexer, t_data **data);
void			get_token_3(t_data **data, t_lexer *lexer);
int				get_type_token(char *value, t_data **data);
void			add_token(t_list_token **list_token, t_data **data);
void			add_token_2(t_list_token **list_token, t_data **data);
char			*get_redirection_token(t_lexer *lexer, t_data **data);
char			*s_quote(t_lexer *lexer);
char			*d_quote(t_lexer *lexer, t_data **data);
char			*d_quote_2(t_lexer *lexer, char *string, t_data **data);
char			*d_quote_3(t_lexer *lexer, t_data **data, char **string);
char			*get_pipe_token(t_lexer *lexer, t_data **data);
char			*get_word_token(t_lexer *lexer, t_data **data);
char			*get_word_token_2(t_lexer *lexer, t_data **data, char **word);
void			get_word_token_3(t_lexer *lexer, t_data **data);
char			*get_value(t_lexer *lexer, t_data **data);

char			*ft_expand(char *word, t_lexer *lexer, t_data **data);
char			*ft_expand_2(char *word, t_lexer *lexer, t_data **data);
int				ft_expand_3(t_lexer *lexer, char **str, char **ptr, char **env);
char			*expand_digit(t_lexer *lexer, char *word, t_data **data);
char			*expand_digit_2(t_lexer *lexer, char *word);

void			convert_type_word(t_list_token **list_token);
t_list_cmd		*get_list_cmd(t_list_token **list_token, t_list_cmd ** list_cmds);
void			add_node_cmd(t_list_cmd **list_cmds, t_list_cmd *new_cmd);
void			init_node(t_list_cmd **new_cmd);
t_list_cmd		*node_list(t_list_token **list_token);
int				nbr_args(t_list_token *list_token);
int				nbr_file_output(t_list_token *list_token);
int				nbr_file_input(t_list_token *list_token);
int				nbr_herdoc(t_list_token *list_token);
#endif