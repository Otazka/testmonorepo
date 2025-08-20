CC = cc
CFLAGS = -Wall -Wextra -Werror -I./incl/
RM = rm -rf
NAME = libftprintf.a

SRCS = ft_printf.c srcs/ft_words.c srcs/ft_numbers.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	ar rc $(NAME) $(OBJS)
clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re

.SILENT: