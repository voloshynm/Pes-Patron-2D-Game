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
		g->state = ESCAPE;
	if (keycode == BUT_UP || keycode == BUT_DOWN
		|| keycode == BUT_LEFT || keycode == BUT_RIGHT)
	{
		move_player_vertically(g, keycode);
		move_player_horizontally(g, keycode);
	}
	return (0);
}

static int	update_game_helper(t_game *g, int animation_frame, int move_made)
{
	int	i;

	if (animation_frame == 0)
	{
		move_foes(g);
		if (g->player->action == 1 || g->player->action == 2
			|| g->player->action == 3)
			move_made = 1;
	}
	draw_game(g, animation_frame);
	if (move_made && animation_frame == 7)
	{
		i = -1;
		g->player->action = 0;
		move_made = 0;
		while (++i < g->cnt->foes && g->state == IN_PLAY)
			g->foe[i].action = 0;
	}
	return (move_made);
}

// Delay in microseconds for ~24 FPS
int	update_game(t_game *g)
{
	int			animation_frame;
	static int	frame = 0;
	static int	move_made = 0;

	usleep(166666);
	if (g->state != IN_PLAY)
		end_game(g);
	else
	{
		animation_frame = frame % 8;
		move_made = update_game_helper(g, animation_frame, move_made);
		frame++;
	}
	return (0);
}

void	end_game(t_game *g)
{
	if (g->state == GAME_OVER)
	{
		ft_printf(
			"▓██   ██▓ ▒█████   █    ██    ▓█████▄  ██▓▓█████ ▓█████▄ \n"
			" ▒██  ██▒▒██▒  ██▒ ██  ▓██▒   ▒██▀ ██▌▓██▒▓█   ▀ ▒██▀ ██▌\n"
			"  ▒██ ██░▒██░  ██▒▓██  ▒██░   ░██   █▌▒██▒▒███   ░██   █▌\n"
			"  ░ ▐██▓░▒██   ██░▓▓█  ░██░   ░▓█▄   ▌░██░▒▓█  ▄ ░▓█▄   ▌\n"
			"  ░ ██▒▓░░ ████▓▒░▒▒█████▓    ░▒████▓ ░██░░▒████▒░▒████▓ \n"
			"   ██▒▒▒ ░ ▒░▒░▒░ ░▒▓▒ ▒ ▒     ▒▒▓  ▒ ░▓  ░░ ▒░ ░ ▒▒▓  ▒ \n"
			" ▓██ ░▒░   ░ ▒ ▒░ ░░▒░ ░ ░     ░ ▒  ▒  ▒ ░ ░ ░  ░ ░ ▒  ▒ \n"
			" ░ ░         ░ ░     ░           ░     ░     ░  ░   ░    \n"
			"\nGAME OVER: Zombie killed you!\n");
	}
	else if (g->state == SUCCESS)
		ft_printf(
			"██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗ ██████╗ ███╗   ██╗\n"
			"╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██╔═══██╗████╗  ██║\n"
			" ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║   ██║██╔██╗ ██║\n"
			"  ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║   ██║██║╚██╗██║\n"
			"   ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝╚██████╔╝██║ ╚████║\n"
			"   ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═══╝\n\n"
			"YOU WON! Congratulations!\n");
	else if (g->state == ESCAPE)
		ft_printf("GAME ENDED\n You decided to stop the game!\n");
	free_game(g);
}
