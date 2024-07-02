/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:05:21 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/07/02 18:05:23 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_STRUCTS_H
# define SO_LONG_STRUCTS_H

# include <stdbool.h>	//bool

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

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
	int			map_x_len;
	int			map_y_len;
	t_counter	*cnt;
	t_actor		*player;
	t_actor		*foe;
	t_texture	*texture;
	int			state;
}	t_game;

// Node for BFS
typedef struct s_node
{
	t_point			pos;
	struct s_node	*next;
}	t_node;

// Queue for BFS
typedef struct s_queue
{
	t_node	*front;
	t_node	*rear;
}	t_queue;

// move direction definition
typedef enum e_direction
{
	NONE,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
}	t_direction;

// best move data, towards the required object
typedef struct s_result
{
	int			min_steps;
	t_point		target;
	t_direction	best_move;
}	t_result;

#endif
