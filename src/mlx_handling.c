#include "../inc/so_long.h"

void	init_mlx(t_game *g)
{
	g->mlx_ptr = mlx_init();
	if (!g->mlx_ptr)
		return (MLX_ERROR);
	g->win_ptr = mlx_new_window(g->mlx_ptr, g->map_y_len * SPRITE_SIZE, 
								g->map_x_len * SPRITE_SIZE, WINDOW_NAME);
	if (!g->win_ptr)
		return (MLX_ERROR);
	load_textures(g);
}

void	key_press(int keycode, t_game *g)
{
	if (keycode == BUT_ESC)
		g->state = GAME_OVER;
	else if (keycode == BUT_UP)
	{
		g->player->next_move.x = g->player->pos.x;
		g->player->next_move.y = g->player->pos.y - 1;
	}
	else if (keycode == BUT_DOWN)
	{
		g->player->next_move.x = g->player->pos.x;
		g->player->next_move.y = g->player->pos.y + 1;
	}
	else if (keycode == BUT_LEFT)
	{
		g->player->next_move.x = g->player->pos.x - 1;
		g->player->next_move.y = g->player->pos.y;
	}
	else if (keycode == BUT_RIGHT)
	{
		g->player->next_move.x = g->player->pos.x + 1;
		g->player->next_move.y = g->player->pos.y;
	}
}

void	init_hooks(t_game *g)
{
	mlx_key_hook(g->win_ptr, key_press, g);
	mlx_loop_hook(g->mlx_ptr, update_game, g);
}

int	update_game(t_game *g)
{
	static int	frame;

	frame = 0;
	if (frame % 10 == 0)
		move_foes(g);
	draw_game(g);
	frame++;
	return (IN_PLAY);
}

void	draw_game(t_game *g, )
{
	draw_tiles(g);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->texture);
}