/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:45:22 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/20 10:01:00 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>

# define GNL_EOF (NULL)
# define GNL_INTERRUPT ((char *)1)

struct s_state {
	char	**env;
	int		exit_status;
	int		readline_done;
};

extern struct s_state	g_state;

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
	char	*buff;
	char	*ling;

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
		TOKEN_AMBIGUOUS_REDIRECTION,
		TOKEN_WORD,
		TOKEN_REDI_OUTPUT,
		TOKEN_FILE_OUT,
		TOKEN_APPAND,
		TOKEN_FILE_APPAND,
		TOKEN_REDI_INPUT,
		TOKEN_FILE_INP,
		TOKEN_HERDOC,
		TOKEN_FILE_HERDOC,
		TOKEN_PIPE,
	} e_type;
	char	*val;
}	t_token;

struct	s_list_cmd;
typedef int	(*t_builtin)(struct s_list_cmd *);

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
	char						**cmds_args;
	t_list_io_stream			*io;
	struct s_list_cmd			*next;
	struct s_list_cmd			*prev;
	pid_t						__pid;
	t_builtin					__builtin;
	int							__builtin_exit_status;
	int							__builtin_stdin;
	int							__builtin_stdout;
	int							__in_subshell;
	int							__is_created;
}	t_list_cmd;


char				*ft_strjoin2(char *string, char c, t_lexer *lexer);
int					ft_strlen(char *str);
char				*ft_strdup(char *src);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strjoin(char *str1, char *str2);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
int					ft_atoi_err(char *str, int *error);
int					ft_strncmp(char *s1, char *s2, size_t n);
void				*ft_calloc(size_t count, size_t size);
char				*ft_itoa(int n);
void				*ft_memset(void *dest, int v, size_t len);
int					ft_search(char *ligne);
char				*ft_ligne(char *buff, int position, int n);
char				*ft_save(char *save, int n);
char				*ft_get_line(char *ligne, char **save, int n);
char				*get_next_line(int fd, t_data **data);

char				*ft_strchr(char *s, int c);
size_t				ft_strlcpy(char *dst, char *src, size_t size);
void				*ft_memcpy(void *dst, void *src, size_t n);
void				*ft_memmove(void *dst, void *src, size_t len);
size_t				ft_strlcat(char *dest, char *src, size_t size);
char				**ft_split(char *str, char c);

char				*char_convert_string(char c);
int					skip_whitespace(t_lexer *lexer);
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
						t_lexer *lexer, t_data **data, t_list_cmd **list_cmd);
int					nbr_args(t_list_token *list_token);

char				*ft_expand_herdoc(char *string_join,
						char **string_inp, t_data **data);
void				remove_space(char **word);
void				ft_find_space(char **word, t_list_token **list_token,
						t_data **data);
int					nbr_word(char *str);
int					len_list(t_list_token **list_cmd);
void				find_space_in_word(char **word, t_data **data);
t_list_token		*end_list(t_list_token **list_token);
void				check_space_in_word(char **word, t_list_token *tmp,
						t_data **data);
int					found_quote(t_lexer *lexer);

int					check_quote_pipe(t_list_token **list_token);
int					check_token(t_list_token **list_token);
void				check_ambiguous(t_list_token **list_token, t_data **data);
int					check_redirection(t_list_token **list_token);
int					is_token_2(int type_token);

char				*ft_herdoc(char *eof, t_data **data, t_lexer *lexer, t_list_cmd **list_cmd);
void				ft_herdoc_2(char **ret_expand, char **string_join,
						char **string_inp, t_data **data);
void				ft_herdoc_3(char **string_inp, t_data **data);

void				add_node_file(t_list_io_stream **inpt_out_file,
						t_list_io_stream *new_file);
t_list_io_stream	*get_io_file(int flags, char **name_file);
int					is_file(int type_token);
int					find_pipe(t_list_token **list_token);

int					__pr_error(char *cmd, char *arg, char *msg, int ret);
int					pr_error(char *cmd, char *arg, int ret);
void				fatal(char *msg, int status);
int					count_processes(struct s_list_cmd *cmd);
int					get_append_flag(struct s_list_io_stream *io);
int					arr_size(char **path);
void				init_prev(struct s_list_cmd *cmd);

void				handle_signals(void);

char				**clone_env(char **env);
char				*get_env(char *name);
void				print_env(int export_mode);
int					valid_env_name(char *var);
int					unset_env(char *name);
int					set_env(char *name_value);

void				init_pipes(int count, int pipes[][2]);
void				get_pipe(int pipes[][2], int pipe[2],
						int *i, int pipe_count);
void				close_unused_pipes(int pipe[2], int pipes[][2], int len);

t_builtin			get_builtin(char *cmd);
int					find_exec(char *exec, char **full_path);

int					arg_equal_flag(char *arg, char flag);

void				handle_pipe(struct s_list_cmd *cmd,
						int pipe[2], int pipes[][2], int len);
int					handle_io(struct s_list_cmd *cmd);
void				save_stdin_stdout(struct s_list_cmd *cmd);
void				restore_stdin_stdout(struct s_list_cmd *cmd);

int					create_child(struct s_list_cmd *cmd, int _pipe[2],
						int pipes[][2], int len);
int					create_children(struct s_list_cmd *cmd,
						int pipe_count, int pipes[][2]);
int					get_exit_code(int status);
int					fetch_exit_status(struct s_list_cmd *cmd);
int					exec(struct s_list_cmd *cmd);
void 				free_all_data(t_data **data, t_list_token **list_token,
						t_list_cmd **list_cmds, t_lexer **input_commands);
#endif