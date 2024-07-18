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

// move direction definition
typedef enum e_dir
{
	NONE,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
}	t_dir;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

// For active game actors (player and enemies)
typedef struct s_actor
{
	t_point	pos;
	t_dir	dir;
	int		action;
	int		d;
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

/*
*	To parse sprite images
*	in intance *player_idle[4][4]; 
	
	the first element is a type of move:
		0 = idle
		1 = walk
		2 = attack
		3 = death
	the second element is face of the actor
		0 = front
		1 = back
		2 = right
		3 = left
*	the third element is a sprite of an animation frame
*/
typedef struct s_texture
{
	void	*player_idle[4][8];
	void	*player_walk[4][8];
	void	*player_hits[4][8];
	void	*player_dead[4][8];
	void	*foe_idle[4][8];
	void	*foe_walk[4][8];
	void	*foe_hits[4][8];
	void	*foe_dead[4][8];
	void	*gem[8];
	void	*exit[8];
	void	*wall[26];
	void	*floor[64];
/*	int		px_size;
	int		px_height;
	int		px_width;*/
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
	int			x_s;
	int			y_s;
	t_counter	*cnt;
	t_actor		*player;
	t_actor		*foe;
	t_texture	*texture;
	int			state;
	int			complexity;
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

// best move data, towards the required object
typedef struct s_result
{
	int		min_steps;
	t_point	target;
	t_dir	best_move;
}	t_result;

typedef struct s_bfs_state
{
	bool	**visited;
	int		**steps;
	t_dir	**directions;
	int		y_s;
	int		x_s;
}	t_bfs_state;

#endif