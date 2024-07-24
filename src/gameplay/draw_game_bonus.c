/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:09:02 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/07/18 22:09:04 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

void	draw_game(t_game *g, int animation_frame)
{
	char	*display_moves;
	char	*cnt_moves_txt;

	draw_map(g, animation_frame);
	draw_foes(g, animation_frame);
	draw_player(g, animation_frame);
	cnt_moves_txt = ft_itoa(g->cnt->moves);
	display_moves = ft_strjoin("Moves taken: ", cnt_moves_txt);
	mlx_string_put(g->mlx_ptr, g->win_ptr, 10, 10, 0xFFFFFF, display_moves);
	free(cnt_moves_txt);
	free(display_moves);
}

void	draw_map(t_game *g, int animation_frame)
{
	int		i;
	int		j;
	t_point	*pos;

	j = -1;
	pos = ft_calloc(1, sizeof(pos));
	while (++j < g->y_s)
	{
		i = -1;
		while (++i < g->x_s)
		{
			pos->x = i;
			pos->y = j;
			if (g->map[j][i] == '1')
				draw_tile(g, g->texture->wall, pos);
			else
				draw_tile(g, g->texture->floor, pos);
			if (g->map[j][i] == 'E'
					&& g->cnt->taken_gems == g->cnt->total_gems)
				draw_gem(g, g->texture->exit, animation_frame, pos);
			else if (g->map[j][i] == 'C')
				draw_gem(g, g->texture->gem, animation_frame, pos);
		}
	}
	free(pos);
}

void	draw_tile(t_game *g, void *item_array[64], t_point *pos)
{
	int	pseudo_rand;

	pseudo_rand = (pos->x * pos->y * 2438747) % 64;
	if (pseudo_rand % 3 == 0 || pseudo_rand % 4 == 0)
		pseudo_rand = 0;
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, item_array[pseudo_rand],
		pos->x * SPRITE_SIZE, pos->y * SPRITE_SIZE);
}

void	draw_gem(t_game *g, void *item_array[64], int f, t_point *pos)
{
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, item_array[f],
		pos->x * SPRITE_SIZE, pos->y * SPRITE_SIZE);
}
