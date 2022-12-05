NAME := ft_printf.o
SRCS := ft_print_char.c ft_print_int.c ft_print_ptr.c ft_print_uint.c main.c ft_print_percent.c ft_print_str.c ft_print_uint_hex.c ft_print_padded_str.c ft_adjust_precision.c ft_format.c ft_check_precision.c ft_flags.c ft_printf.c
OBJS := $(SRCS:.c=.o)
CFLAGS := -Wall -Wextra -Werror
LD := ld
LDFLAGS := -r

all: $(NAME)

$(NAME): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	-rm $(OBJS)

fclean: clean
	-rm $(NAME)

re: fclean all