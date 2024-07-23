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

int	main(int argc, char **argv)
{
	t_game	g;

	g.game_name = WINDOW_NAME;
	g.sprite_size = SPRITE_SIZE * SCALE_FACTOR;
	init_game(&g, argc, argv);
	while (g.state == IN_PLAY)
		update_game(&g);
	if (g.state == GAME_OVER || g.state == SUCCESS || g.state == ESCAPE)
		free(g.mlx_ptr);
}
