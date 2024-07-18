/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:12:15 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/07/18 21:12:17 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

void	init_mlx(t_game *g)
{
	g->mlx_ptr = mlx_init();
	if (!g->mlx_ptr)
	{
		g->state = MLX_ERROR;
		return ;
	}
	g->win_ptr = mlx_new_window(g->mlx_ptr, g->y_s * SPRITE_SIZE,
			g->x_s * SPRITE_SIZE, WINDOW_NAME);
	if (!g->win_ptr)
	{
		g->state = MLX_ERROR;
		return ;
	}
	load_textures(g);
}

int	update_game(t_game *g)
{
	static int	frame;

	frame = 0;
	if (frame % 10 == 0)
		move_foes(g);
	draw_game(g, frame);
	frame++;
	return (IN_PLAY);
}

void	draw_game(t_game *g, int frame)
{
	draw_tiles(g, frame);
	draw_gems(g, frame);
	draw_foes(g, frame);
	draw_player(g, frame);
	if (g->cnt->taken_gems == g->cnt->total_gems)
		draw_exit(g, frame);
}

void	key_press(int keycode, t_game *g)
{
	if (keycode == BUT_ESC)
		g->state = GAME_OVER;
	if (keycode == BUT_UP || keycode == BUT_DOWN
		|| keycode == BUT_LEFT || keycode == BUT_RIGHT)
		move_player(g, keycode);
}

void	init_hooks(t_game *g)
{
	mlx_key_hook(g->win_ptr, key_press, g);
	mlx_loop_hook(g->mlx_ptr, update_game, g);
}
