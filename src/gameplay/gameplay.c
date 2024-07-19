/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:25:20 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/07/19 20:25:22 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

int	key_press(int keycode, t_game *g)
{
	if (keycode == BUT_ESC)
		g->state = GAME_OVER;
	if (keycode == BUT_UP || keycode == BUT_DOWN
		|| keycode == BUT_LEFT || keycode == BUT_RIGHT)
	{
		move_player_vertically(g, keycode);
		move_player_horizontally(g, keycode);
	}
	return (0);
}

int	update_game(t_game *g)
{
	int			animation_frame;
	static int	frame = 0;

	animation_frame = frame % 8;
	if (animation_frame == 0)
		move_foes(g);
	draw_game(g, animation_frame);
	ft_printf("Steps made: %d\n", g->cnt->moves);
	frame++;
	return (0);
}

void	draw_game(t_game *g, int animation_frame)
{
	int	i;
	int	j;

	j = -1;
	while (++j < g->y_s)
	{
		i = -1;
		while (++i < g->x_s)
		{
			if (g->map[j][i] == '1')
				draw_wall(g, i, j);
			else
				draw_floor(g, i, j);
			if (g->map[j][i] == 'E' && g->cnt->taken_gems == g->cnt->total_gems)
				draw_exit(g, animation_frame, i, j);
			else if (g->map[j][i] == 'C')
				draw_gems(g, animation_frame, i, j);
		}
	}
	draw_foes(g, animation_frame);
	draw_player(g, animation_frame);
}

void	game_over(t_game *g)
{
	if (g->state == GAME_OVER)
		ft_printf("GAME OVER\n: You lost!\n");
	else if (g->state == SUCCESS)
		ft_printf("YOU WON!\n Congratulations!\n");
}
