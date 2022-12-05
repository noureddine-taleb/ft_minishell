SRC := ft_strcmp.c ft_abs.c ft_atoi.c ft_atoi_err.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c get_next_line.c ft_putmem_fd.c ft_utoa_base.c
OBJ := $(SRC:.c=.o) ft_printf/ft_printf.o
CFLAGS := -Wall -Wextra -Werror -D BUFFER_SIZE=1000

AR := ar
ARFLAGS := cr

NAME := libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

ft_printf/ft_printf.o:
	$(MAKE) -C ft_printf

clean:
	-rm $(OBJ)
	-$(MAKE) -C ft_printf clean

fclean: clean
	-rm $(NAME)
	-$(MAKE) -C ft_printf fclean

re: fclean all
