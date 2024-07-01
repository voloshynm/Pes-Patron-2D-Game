#ifndef SO_LONG_STRUCTS_H
# define SO_LONG_STRUCTS_H

# include <stdbool.h>	//bool

typedef struct s_point
{
    int x;
	int y;
} t_point;

// For active game actors (player and enemies)
typedef struct s_actor
{
	t_point	pos;
	t_point	best_move;
}	t_actor;

// To cnt items for map validation and gameplay 
typedef struct s_counter
{
	int	players;
	int	foes;
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
	void	*foe_l[4];
	void	*foe_r[4];
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
	long		map_x_len;
	long		map_y_len;
	t_counter	*cnt;
	t_actor		*player;
	t_actor		*foe;
	t_texture	*texture;
	int			state;
}	t_game;

#endif