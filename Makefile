SRC = 	src/main.c					\
		src/init/utils.c			\
		src/init/init_game.c		\
		src/init/init_mlx.c			\
		src/init/load_textures.c	\
		src/init/free_game.c		\
		src/gameplay/gameplay.c		\
		src/gameplay/bfs.c			\
		src/gameplay/bfs_utils.c	\
		src/gameplay/draw_game.c	\
		src/gameplay/foe.c			\
		src/gameplay/player.c
OBJS = ${SRC:.c=.o}
NAME = so_long

CC = cc -g
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
	curl -LOJ https://cdn.intra.42.fr/document/document/26474/minilibx-linux.tgz
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
