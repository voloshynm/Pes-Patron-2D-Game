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
# define UP		119		//W key
# define DOWN	115		//A key
# define LEFT	97		//S key
# define RIGHT	100		//D key
# define ESC	65307	//ESC key

// Colours & Other Constants
# define RED	"\033[1m\033[31m"
# define GREEN	"\033[1m\033[32m"
# define ENDC	"\033[0m"
# define WINDOW_NAME	"DOG PATRON GAME"
# define SPRITE_SIZE	32
# define GO_UP -1
# define GO_DOWN 1
# define GO_LEFT -1
# define GO_RIGHT 1

enum e_state
{
	IN_PLAY = 1,
	GAME_OVER = -1,
	ARG_ERROR = -2,
	MAP_ERROR = -3,
	IMAGE_INIT = 5
};

#endif