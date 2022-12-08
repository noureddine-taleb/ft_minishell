LIBFT_DIR := ../libft
LIBFT := $(LIBFT_DIR)/libft.a
SRCS := main.c ../exec.c
TARGET := minishell
CFLAGS := -g -Wall -Wextra

all: $(TARGET)

$(LIBFT): $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR)

$(TARGET): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^
