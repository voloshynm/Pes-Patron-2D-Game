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
typedef struct s_counter
{
	int	players;
	int	enemies;
	int	exits;
	int	total_gems;
	int	taken_gems;
	int	moves;
}	t_counter;

// To parse sprite
typedef struct s_texture
{
	void	*player_l[4];
	void	*player_r[4];
	void	*enemy_l[4];
	void	*enemy_r[4];
	void	*gem[4];
	void	*exit[2];
	void	*wall;
	void	*floor;
	int		*px_size;
	int		*px_height;
	int		*px_width;
	int		keyframe;
	int		frame;
}	t_texture;

// Gameplay
typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	char		*tmp_line;
	int			map_x_len;
	int			map_y_len;
	t_counter	*cnt;
	t_actor		*player;
	t_actor		**enemies;
	t_texture	*texture;
	int			state;
}	t_game;

#endif