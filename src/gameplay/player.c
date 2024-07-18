/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_gameplay.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:47:34 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/07/18 19:47:36 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

static bool	is_accessible_player(t_game *g, int x_off, int y_off)
{
	if (g->map[g->player->pos.y + y_off][g->player->pos.x + x_off] == 'F'
		|| g->map[g->player->pos.y + y_off][g->player->pos.x + x_off] == 'C'
		|| g->map[g->player->pos.y + y_off][g->player->pos.x + x_off] == 'E'
		|| g->map[g->player->pos.y + y_off][g->player->pos.x + x_off] == '0')
		return (true);
	return (false);
}

static void	action_player(t_game *g)
{
	g->player->action = 0;
	if (g->map[g->player->pos.y][g->player->pos.x] == 'F')
	{
		g->player->action = 3;
		g->state = GAME_OVER;
	}
	else if (g->map[g->player->pos.y][g->player->pos.x] == 'C')
	{
		g->player->action = 2;
		g->cnt->taken_gems += 1;
	}
	else if (g->map[g->player->pos.y][g->player->pos.x] == 'E'
			&& g->cnt->taken_gems == g->cnt->total_gems)
	{
		g->player->action = 2;
		g->state = SUCCESS;
	}
	else
		g->player->action = 1;
	g->map[g->player->pos.y][g->player->pos.x] = 'P';
	draw_game(g);
}

void	move_player(t_game *g, int keycode)
{
	if (keycode == BUT_UP && is_accessible_player(g, 0, -1))
	{
		g->map[g->player->pos.y][g->player->pos.x] = '0';
		g->player->dir = MOVE_UP;
		g->player->pos.y -= 1;
	}
	else if (keycode == BUT_DOWN && is_accessible_player(g, 0, 1))
	{
		g->map[g->player->pos.y][g->player->pos.x] = '0';
		g->player->dir = MOVE_DOWN;
		g->player->pos.y += 1;
	}
	else if (keycode == BUT_LEFT && is_accessible_player(g, -1, 0))
	{
		g->map[g->player->pos.y][g->player->pos.x] = '0';
		g->player->dir = MOVE_LEFT;
		g->player->pos.x -= 1;
	}
	else if (keycode == BUT_RIGHT && is_accessible_player(g, 1, 0))
	{
		g->map[g->player->pos.y][g->player->pos.x] = '0';
		g->player->dir = MOVE_RIGHT;
		g->player->pos.x += 1;
	}
	action_player(g);
}

void	draw_player(t_game *g, int f)
{
	if (g->player->dir == MOVE_UP)
		g->player->d = 1;
	else if (g->player->dir == MOVE_DOWN)
		g->player->d = 0;
	else if (g->player->dir == MOVE_LEFT)
		g->player->d = 3;
	else if (g->player->dir == MOVE_RIGHT)
		g->player->d = 2;
	if (g->player->action == 0)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->player_idle[g->player->d][f], g->player->pos.x, g->player->pos.y);
	else if (g->player->action == 1)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->player_walk[g->player->d][f], g->player->pos.x, g->player->pos.y);
	else if (g->player->action == 2)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->player_hits[g->player->d][f], g->player->pos.x, g->player->pos.y);
	else if (g->player->action == 3)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->player_dead[g->player->d][f], g->player->pos.x, g->player->pos.y);
}
