/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:05:13 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/07/02 18:05:15 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "so_long_structs.h"		//structs for the program
# include "../libft/libft.h"		//own libft library
# include "../libft/ft_printf.h"	//custom printf
# include "../libft/get_next_line.h"//custom get_next_line
# include "../minilibx/mlx.h"		//mlx
# include "../minilibx/mlx_int.h"	//mlx internal

# include <fcntl.h>					//open, O_RDONLY
# include <unistd.h>				//read, close, write
# include <stdlib.h>				//malloc
# include <stdbool.h>				//bool
# include <time.h>					//bonus delay

// Buttons listeners
# define BUT_UP		119				//W key
# define BUT_DOWN	115				//A key
# define BUT_LEFT	97				//S key
# define BUT_RIGHT	100				//D key
# define BUT_ESC	65307			//ESC key

// Colours & Other Constants
# define RED			"\033[1m\033[31m"
# define GREEN			"\033[1m\033[32m"
# define ENDC			"\033[0m"
# define WINDOW_NAME	"WALKING DEAD GAME"
# define SPRITE_SIZE	32

enum e_state
{
	IN_PLAY = 1,
	GAME_OVER = -1,
	ARG_ERROR = -2,
	MAP_ERROR = -3,
	ALLOC_ERROR = -4,
	MLX_ERROR = -5,
	SUCCESS = 2
};

//Functions

// Initializing the game, MLX & utils
void		init_game(t_game *g, int argc, char **argv);
int			init_map(t_game *g, char *file_name);
int			parse_map(t_game *g);
int			init_map_counters(t_game *g);
int			get_number_of_lines(char *file_name);
int			validate_file_name(char *s);
void		init_mlx(t_game *g);
void		init_hooks(t_game *g);
void		load_textures(t_game *g);
void		free_game(t_game *g);

// Gameplay
int			update_game(t_game *g);
void		draw_game(t_game *g, int animation_frame);
int			key_press(int keycode, t_game *g);
void		game_over(t_game *g);
void		move_foes(t_game *g);
void		move_player_horizontally(t_game *g, int keycode);
void		move_player_vertically(t_game *g, int keycode);

// BFS & its Utils
t_result	best_move_to_object(t_game *g, char obj, t_actor *actor);
void		enqueue(t_queue *q, t_point pos);
t_point		dequeue(t_queue *q);
t_bfs_state	*init_bfs_state(int rows, int cols);
void		free_bfs_state(t_bfs_state *state);

// Draw textures
void		draw_game(t_game *g, int animation_frame);
void		draw_player(t_game *g, int f);
void		draw_foes(t_game *g, int f);
void		draw_wall(t_game *g, int x, int y);
void		draw_floor(t_game *g, int x, int y);
void		draw_gems(t_game *g, int f, int x, int y);
void		draw_exit(t_game *g, int f, int x, int y);

#endif
