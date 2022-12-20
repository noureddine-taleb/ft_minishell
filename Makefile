# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 18:43:49 by kadjane           #+#    #+#              #
#    Updated: 2022/12/20 13:16:42 by ntaleb           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = parser.c get_next_line.c free_all.c\
		token/token.c token/token_2.c\
		token/word_token.c token/word_token_2.c\
		token/d_quote.c token/red_squote_pip.c\
		utils/fuc_util.c utils/fun_util_2.c utils/fun_util_3.c utils/fun_util_4.c utils/fun_util_5.c utils/fun_util_6.c\
		utils/fun_whitespace.c utils/fun_find_space.c utils/ft_atoi_err.c utils/ft_split.c utils/ft_itoa.c \
		expand_herdoc/expand.c expand_herdoc/expand_in_herdoc.c expand_herdoc/fun_herdoc.c\
		lexer_get_file/fun_free.c lexer_get_file/lexer.c lexer_get_file/node.c lexer_get_file/fun_error.c\
		lexer_get_file/get_file.c lexer_get_file/get_file_2.c lexer_get_file/get_file_3.c\
		exec/init.c exec/builtins.c exec/builtins2.c \
		exec/env.c exec/env2.c exec/env3.c exec/exec.c exec/exec2.c exec/helpers.c \
		exec/helpers2.c exec/io.c exec/io2.c exec/path.c exec/path2.c \
		exec/pipe.c exec/signal.c exec/flags.c 
		

OBJS = $(SRCS:.c=.o) 

CC = cc

LDFLAGS = -lreadline -L $(HOME)/.brew/opt/readline/lib
CFLAGS = -Wall -Wextra -Werror -I $(HOME)/.brew/opt/readline/include #-fsanitize=address -g3

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean :
	@rm -f **/*.o *.o
fclean : clean
	@rm -f $(NAME)
re : fclean all