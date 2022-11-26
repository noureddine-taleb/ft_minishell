# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 18:43:49 by kadjane           #+#    #+#              #
#    Updated: 2022/11/26 22:05:37 by kadjane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = parser.c token.c token_2.c fuc_util.c fun_util_2.c fun_free.c token_3.c lexer.c node.c

NAME = minishell

OBJS = $(SRCS:.c=.o) 

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME) -lreadline
clean : 
	@rm -f *.o
fclean : clean
	@rm -f $(NAME)
re : fclean all