SRC	= 	src/main.c				

OBJS	= ${SRC:.c=.o}

NAME = so_long

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -I./minilibx -I./libft -I./inc

LDFLAGS	= -L./minilibx -lmlx -L./libft -lft -lm -lXext -lX11

all:		minilibx/libmlx.a libft/libft.a $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

minilibx/libmlx.a:
	$(MAKE) -C minilibx

libft/libft.a:
	$(MAKE) -C libft

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re

