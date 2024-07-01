SRC = 	src/main.c	\
		src/init_game.c			
OBJS = ${SRC:.c=.o}
NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./minilibx -I./libft -I./inc
LDFLAGS = -L./minilibx -lmlx -L./libft -lft -lm -lXext -lX11

all: minilibx/libmlx.a libft/libft.a $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

minilibx/libmlx.a: minilibx
	$(MAKE) -C minilibx

minilibx:
	curl -LOJ https://cdn.intra.42.fr/document/document/24017/minilibx-linux.tgz
	tar -xzf minilibx-linux.tgz
	mv minilibx-linux minilibx
	rm -r minilibx-linux.tgz

libft/libft.a:
	git clone git@github.com:Harley-Davidson/libft.git libft
	$(MAKE) -C libft

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean
	if [ -d minilibx ]; then $(MAKE) -C minilibx clean; fi

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	rm -rf minilibx minilibx-linux.tgz libft

re: fclean all

.PHONY: all clean fclean re
