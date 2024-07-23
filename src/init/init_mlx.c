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
	g->win_ptr = mlx_new_window(g->mlx_ptr, g->x_s * SPRITE_SIZE * SCALE_FACTOR,
			g->y_s * SPRITE_SIZE * SCALE_FACTOR, WINDOW_NAME);
	if (!g->win_ptr)
	{
		g->state = MLX_ERROR;
		return ;
	}
	load_textures(g);
}

int	handle_close(t_game *g)
{
	g->state = ESCAPE;
	return (0);
}

void	init_hooks(t_game *g)
{
	mlx_key_hook(g->win_ptr, (int (*)(int, t_game *))key_press, g);
	mlx_loop_hook(g->mlx_ptr, update_game, g);
	mlx_hook(g->win_ptr, CLOSE_WIND, 0, handle_close, g);
	mlx_loop(g->mlx_ptr);
}
