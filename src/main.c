/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:33:00 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/06/12 19:33:07 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/so_long.h"

int	game_loop(t_game *game)
{
	while (1)
	{
		mlx_hook(game->mlx_ptr, KeyPress, KeyPressMask, &on_keypress, data);
		mlx_hook(game->win_ptr, DestroyNotify, StructureNotifyMask,
			&game_destroy, data);
		mlx_loop_hook(game->mlx_ptr, &refresh, data);
		mlx_loop(game->mlx_ptr);
	}
	return (0);
}


int main(int argc, char **argv)
{
    t_game  game;
    
    init_game(&game, argc, argv);
	game_loop(&game);
	free_game(&game);
}
