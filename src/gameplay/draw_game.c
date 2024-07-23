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
	int		i;
	int		j;
	char	*display_moves;
	char	*cnt_moves_txt;

	j = -1;
	while (++j < g->y_s)
	{
		i = -1;
		while (++i < g->x_s)
		{
			if (g->map[j][i] == '1')
				draw_tile(g, g->texture->wall, i * SCALE_FACTOR, j * SCALE_FACTOR);
			else
				draw_tile(g, g->texture->floor, i * SCALE_FACTOR, j * SCALE_FACTOR);
			if (g->map[j][i] == 'E' && g->cnt->taken_gems == g->cnt->total_gems)
				draw_gem(g, g->texture->exit, animation_frame, i * SCALE_FACTOR, j * SCALE_FACTOR);
			else if (g->map[j][i] == 'C')
				draw_gem(g, g->texture->gem, animation_frame, i * SCALE_FACTOR, j * SCALE_FACTOR);
		}
	}
	draw_foes(g, animation_frame);
	draw_player(g, animation_frame);
	cnt_moves_txt = ft_itoa(g->cnt->moves);
	display_moves = ft_strjoin("Moves taken: ", cnt_moves_txt); 
	mlx_string_put(g->mlx_ptr, g->win_ptr, 10, 10, 0xFFFFFF, display_moves);
	free(cnt_moves_txt);
	free(display_moves);
}

void	draw_player(t_game *g, int f)
{
	if (g->player->dir == MOVE_UP)
		g->player->d = 1;
	else if (g->player->dir == MOVE_DOWN || g->player->dir == NONE)
		g->player->d = 0;
	else if (g->player->dir == MOVE_LEFT)
		g->player->d = 3;
	else if (g->player->dir == MOVE_RIGHT)
		g->player->d = 2;
	if (g->player->action == 0 || g->player->action == -1)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->player_idle[g->player->d][f], g->player->pos.x * g->sprite_size, g->player->pos.y * g->sprite_size);
	else if (g->player->action == 1)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->player_walk[g->player->d][f], g->player->pos.x * g->sprite_size, g->player->pos.y * g->sprite_size);
	else if (g->player->action == 2)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->player_hits[g->player->d][f], g->player->pos.x * g->sprite_size, g->player->pos.y * g->sprite_size);
	else if (g->player->action == 3)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->player_dead[g->player->d][f], g->player->pos.x * g->sprite_size, g->player->pos.y * g->sprite_size);
}

void	draw_foes(t_game *g, int f)
{
	int	i;

	i = -1;
	while (++i < g->cnt->foes)
	{
		g->foe[i].d = 0;
		if (g->foe[i].dir == MOVE_UP)
			g->foe[i].d = 1;
		else if (g->foe[i].dir == MOVE_LEFT)
			g->foe[i].d = 3;
		else if (g->foe[i].dir == MOVE_RIGHT)
			g->foe[i].d = 2;
		if (g->foe[i].action == 0 || g->player->action == -1)
			mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
				->foe_idle[g->foe[i].d][f], g->foe[i].pos.x  * g->sprite_size , g->foe[i].pos.y * g->sprite_size);
		else if (g->foe[i].action == 1)
			mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
				->foe_walk[g->foe[i].d][f], g->foe[i].pos.x * g->sprite_size, g->foe[i].pos.y * g->sprite_size);
		else if (g->foe[i].action == 2)
			mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
				->foe_hits[g->foe[i].d][f], g->foe[i].pos.x * g->sprite_size, g->foe[i].pos.y * g->sprite_size);
		else if (g->foe[i].action == 3)
			mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
				->foe_dead[g->foe[i].d][f], g->foe[i].pos.x * g->sprite_size, g->foe[i].pos.y * g->sprite_size);
	}
}

void	draw_tile(t_game *g, void *item_array[64], int x, int y)
{
	int	pseudo_rand;

	pseudo_rand = (x * y * 2438747) % 64;
	if (pseudo_rand % 3 == 0 || pseudo_rand % 4 == 0)
		pseudo_rand = 0;
//	ft_printf("pseudo rand: %d\n", pseudo_rand);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr,
		item_array[pseudo_rand], x * g->sprite_size, y * g->sprite_size);
}

void	draw_gem(t_game *g, void *item_array[64], int f, int x, int y)
{
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, item_array[f], x * g->sprite_size, y * g->sprite_size);
}
