/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:11:39 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/07/18 21:11:40 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

static bool	is_accessible_foe(t_game *g, t_actor *foe, int x_off, int y_off)
{
	if (g->map[foe->pos.y + y_off][foe->pos.x + x_off] == 'P'
		|| g->map[foe->pos.y + y_off][foe->pos.x + x_off] == 'C'
		|| g->map[foe->pos.y + y_off][foe->pos.x + x_off] == 'E'
		|| g->map[foe->pos.y + y_off][foe->pos.x + x_off] == '0')
		return (true);
	return (false);
}

static void	action_foe(t_game *g, t_actor *foe)
{
	foe->action = 0;
	if (g->map[foe->pos.y][foe->pos.x] == 'P')
	{
		foe->action = 2;
		g->state = GAME_OVER;
	}
	else if ((foe->pos.x - g->player->pos.x < 2 && foe->pos.x - g->player->pos.x
			> -2) || (foe->pos.y - g->player->pos.y < 2 && foe->pos.y
			- g->player->pos.y > -2))
		foe->action = 2;
	else
		foe->action = 1;
	if (g->map[foe->pos.y][foe->pos.x] == '0')
		g->map[foe->pos.y][foe->pos.x] = 'F';
//	print_map(g);
}

static void	clean_old_position(t_game *g, t_actor *foe)
{
	if (g->map[foe->pos.y][foe->pos.x] == 'F')
		if ((foe->dir == MOVE_UP && is_accessible_foe(g, foe, 0, -1))
			|| (foe->dir == MOVE_DOWN && is_accessible_foe(g, foe, 0, 1))
			|| (foe->dir == MOVE_LEFT && is_accessible_foe(g, foe, -1, 0))
			|| (foe->dir == MOVE_RIGHT && is_accessible_foe(g, foe, 1, 0)))
			g->map[foe->pos.y][foe->pos.x] = '0';
}

static void	move_foe(t_game *g, t_actor *foe)
{
	foe->dir = best_move_to_object(g, 'P', foe).best_move;
	clean_old_position(g, foe);
	if (foe->dir == MOVE_UP && is_accessible_foe(g, foe, 0, -1))
	{
		foe->dir = MOVE_UP;
		foe->pos.y -= 1;
	}
	else if (foe->dir == MOVE_DOWN && is_accessible_foe(g, foe, 0, 1))
	{
		foe->dir = MOVE_DOWN;
		foe->pos.y += 1;
	}
	else if (foe->dir == MOVE_LEFT && is_accessible_foe(g, foe, -1, 0))
	{
		foe->dir = MOVE_LEFT;
		foe->pos.x -= 1;
	}
	else if (foe->dir == MOVE_RIGHT && is_accessible_foe(g, foe, 1, 0))
	{
		foe->dir = MOVE_RIGHT;
		foe->pos.x += 1;
	}
	action_foe(g, foe);
}

void	move_foes(t_game *g)
{
	int	i;

	i = -1;
	while (++i < g->cnt->foes && g->state == IN_PLAY)
	{
		move_foe(g, &(g->foe[i]));
	}
}
