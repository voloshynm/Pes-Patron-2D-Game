#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"

typedef struct s_map
{
	char	**map;
	int		x_size;
	int		y_size;
	int		cnt_player;
	int		cnt_enemies;
	int		cnt_exit;
	int		cnt_collects;
	int		cnt_moves;

	

	bool	is_correct;
	bool			is_above_med;
	struct s_node	*prev;
	struct s_node	*next;
	struct s_node	*target_node;
}	t_map;

// map

// other utils


#endif