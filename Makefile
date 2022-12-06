# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 18:43:49 by kadjane           #+#    #+#              #
#    Updated: 2022/12/06 06:56:25 by kadjane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = parser.c\
		token.c token_2.c\
		word_token.c d_quote.c red_squote_pip.c\
		fuc_util.c fun_util_2.c fun_free.c\
		lexer.c expand.c node.c get_file.c

NAME = minishell

OBJS = $(SRCS:.c=.o) 

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME) -lreadline
clean : 
	@rm -f *.o
fclean : clean
	@rm -f $(NAME)
re : fclean all