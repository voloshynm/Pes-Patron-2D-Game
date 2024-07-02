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

# include "so_long_structs.h"
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"

# include <fcntl.h>		//open, O_RDONLY
# include <unistd.h>	//read, close, write
# include <stdlib.h>	//malloc
# include <stdbool.h>	//bool
# include <time.h>		//bonus delay

// Buttons listeners
# define BUT_UP		119		//W key
# define BUT_DOWN	115		//A key
# define BUT_LEFT	97		//S key
# define BUT_RIGHT	100		//D key
# define BUT_ESC	65307	//ESC key

// Colours & Other Constants
# define RED	"\033[1m\033[31m"
# define GREEN	"\033[1m\033[32m"
# define ENDC	"\033[0m"
# define WINDOW_NAME	"DOG PATRON GAME"
# define SPRITE_SIZE	32

enum e_state
{
	IN_PLAY = 1,
	GAME_OVER = -1,
	ARG_ERROR = -2,
	MAP_ERROR = -3,
	ALLOC_ERROR = -4,
	IMAGE_INIT = 5
};

//Functions

// Initializing the game
int		init_map(t_game *g, char *file_name);
void	init_game(t_game *g, int argc, char **argv);

// BFS & its Utils
t_result	best_move_to_object(t_game *g, char obj, t_actor *actor);
void	init_queue(t_queue *q);
void	free_queue(t_queue *q);
void	enqueue(t_queue *q, t_point pos);
t_point	dequeue(t_queue *q);

// Utils
int		get_number_of_lines(char *file_name);

#endif
