#include "../../inc/so_long.h"

void	draw_player(t_game *g, int f)
{
	int	x;
	int	y;

	x = g->player->pos.x;
	y = g->player->pos.y;
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
			->player_idle[g->player->d][f], x * SPRITE_SIZE, y * SPRITE_SIZE);
	else if (g->player->action == 1)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->player_walk[g->player->d][f], x * SPRITE_SIZE, y * SPRITE_SIZE);
	else if (g->player->action == 2)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->player_hits[g->player->d][f], x * SPRITE_SIZE, y * SPRITE_SIZE);
	else if (g->player->action == 3)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->player_dead[g->player->d][f], x * SPRITE_SIZE, y * SPRITE_SIZE);
}

static void	draw_foes_helper(t_game *g, int f, int i)
{
	if (g->foe[i].action == 0 || g->player->action == -1)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->foe_idle[g->foe[i].d][f], g->foe[i].pos.x * SPRITE_SIZE,
			g->foe[i].pos.y * SPRITE_SIZE);
	else if (g->foe[i].action == 1)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->foe_walk[g->foe[i].d][f], g->foe[i].pos.x * SPRITE_SIZE,
			g->foe[i].pos.y * SPRITE_SIZE);
	else if (g->foe[i].action == 2)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->foe_hits[g->foe[i].d][f], g->foe[i].pos.x * SPRITE_SIZE,
			g->foe[i].pos.y * SPRITE_SIZE);
	else if (g->foe[i].action == 3)
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture
			->foe_dead[g->foe[i].d][f], g->foe[i].pos.x * SPRITE_SIZE,
			g->foe[i].pos.y * SPRITE_SIZE);
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
		draw_foes_helper(g, f, i);
	}
}
