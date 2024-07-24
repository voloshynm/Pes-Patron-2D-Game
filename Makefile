SRC =	src/main.c						\
		src/init/utils.c				\
		src/init/init_game.c			\
		src/init/parse_map.c			\
		src/init/init_mlx.c				\
		src/init/load_textures.c		\
		src/init/free_game.c			\
		src/gameplay/gameplay.c			\
		src/gameplay/bfs.c				\
		src/gameplay/bfs_utils.c		\
		src/gameplay/draw_actors.c		\
		src/gameplay/draw_game.c		\
		src/gameplay/foe.c				\
		src/gameplay/player.c

SRC_bonus =	src/main.c					\
		src/init/utils.c				\
		src/init/init_game.c			\
		src/init/parse_map_bonus.c		\
		src/init/init_mlx.c				\
		src/init/load_textures.c		\
		src/init/free_game.c			\
		src/gameplay/gameplay.c			\
		src/gameplay/bfs.c				\
		src/gameplay/bfs_utils.c		\
		src/gameplay/draw_actors.c		\
		src/gameplay/draw_game_bonus.c	\
		src/gameplay/foe.c				\
		src/gameplay/player_bonus.c

OBJDIR = objects
OBJDIR_bonus = objects_bonus
OBJS = $(SRC:src/%.c=$(OBJDIR)/%.o)
OBJS_bonus = $(SRC_bonus:src/%.c=$(OBJDIR_bonus)/%.o)
NAME = so_long
NAME_bonus = so_long_bonus

CC = cc -g
CFLAGS = -Wall -Wextra -Werror -I./minilibx -I./libft -I./inc
LDFLAGS = -L./minilibx -lmlx -L./libft -lft -lm -lXext -lX11

all: minilibx/libmlx.a libft/libft.a $(NAME)

bonus: minilibx/libmlx.a libft/libft.a $(NAME_bonus)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(NAME_bonus): $(OBJS_bonus)
	$(CC) $(CFLAGS) -o $(NAME_bonus) $(OBJS_bonus) $(LDFLAGS)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR_bonus)/%.o: src/%.c
	@mkdir -p $(dir $@)
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
	rm -f $(OBJS) $(OBJS_bonus)
	$(MAKE) -C libft clean
	if [ -d minilibx ]; then $(MAKE) -C minilibx clean; fi

fclean: clean
	rm -f $(NAME) $(NAME_bonus)
	$(MAKE) -C libft fclean
	rm -rf minilibx minilibx-linux.tgz libft $(OBJDIR) $(OBJDIR_bonus)

re: fclean all

.PHONY: all clean fclean re bonus
