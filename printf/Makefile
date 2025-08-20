CC = cc
CFLAGS = -Wall -Wextra -Werror -I./incl/
RM = rm -rf
NAME = libftprintf.a
LIBFT_PATH = ../libft

SRCS = srcs/ft_printf.c srcs/ft_words.c srcs/ft_numbers.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_PATH)
	cp $(LIBFT_PATH)/libft.a $(NAME)
	ar rc $(NAME) $(OBJS)
clean:
	$(MAKE) clean -C $(LIBFT_PATH)
	$(RM) $(OBJS)
fclean: clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re

.SILENT: