# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 18:43:49 by kadjane           #+#    #+#              #
#    Updated: 2022/12/17 15:02:45 by kadjane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = parser.c\
		token.c token_2.c\
		word_token.c word_token_2.c\
		d_quote.c red_squote_pip.c\
		fuc_util.c fun_util_2.c fun_util_3.c fun_util_4.c  fun_free.c\
		lexer.c node.c fun_error.c fun_whitespace.c\
		get_file.c get_file_2.c get_file_3.c\
		expand.c expand_in_herdoc.c ft_itoa.c \
		fun_find_space.c fun_herdoc.c exec/builtins.c exec/env.c exec/helpers.c exec/io.c exec/path.c exec/pipe.c exec/signal.c exec/exec.c

NAME = minishell

OBJS = $(SRCS:.c=.o) 

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME) -lreadline
clean : 
	@rm -f **/*.o *.o
fclean : clean
	@rm -f $(NAME)
re : fclean all