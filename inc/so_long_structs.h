#ifndef SO_LONG_STRUCTS_H
# define SO_LONG_STRUCTS_H

# include <stdbool.h>	//bool

// To store item's coordinates
typedef struct s_coordinates
{
	int	x;
	int	y;
}	t_coordinates;

// For active game actors (player and enemies)
typedef struct s_actor
{
	t_coordinates	*position;
	t_coordinates	*best_move;
}	t_actor;

// To cnt items for map validation and gameplay 
typedef struct s_map_counter
{
	int	players;
	int	enemies;
	int	exits;
	int	total_gems;
	int	taken_gems;
}	t_map_counter;

// 2D plot and it's features
typedef struct s_map
{
	char			**plot;
	char			*tmp_line;
	int				x_size;
	int				y_size;
	t_map_counter	*cnt;
	bool			is_valid;
}	t_map;

// To parse sprite
typedef struct s_img
{
	void	*ptr;
	int		*pixels;
	int		line_size;
	int		mem;
	int		x;
	int		y;
	int		movements;
}	t_img;

// Gameplay
typedef struct s_game
{
	void		*mlx_pointer;
	void		*window_pointer;
	t_map		*map;
	t_actor		*player;
	t_actor		**enemies;
	bool		is_win;
	bool		is_defeat;
	int			cnt_moves;
}	t_game;

#endif