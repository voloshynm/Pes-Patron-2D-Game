/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:04:28 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/07/02 18:04:29 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	DEBUGGING, paste after line 151
	t_result	res;
	i = -1;
	while (++i < g->map_y_len)
		ft_printf("%s\n", g->map[i]);
	ft_printf("It's players %d\n", g->cnt->players);
	ft_printf("It's foes %d\n", g->cnt->foes);
	ft_printf("It's exits %d\n", g->cnt->exits);
	ft_printf("It's total_gems %d\n", g->cnt->total_gems);
	ft_printf("It's taken_gems %d\n", g->cnt->taken_gems);
	ft_printf("It's moves %d\n", g->cnt->moves);
//	ft_printf("Foe x: %d\n", g->foe[0].pos.x);
//	ft_printf("Foe y: %d\n", g->foe[0].pos.y);
	ft_printf("PLayer x: %d\n", g->player[0].pos.x);
	ft_printf("PLayer y: %d\n", g->player[0].pos.y);
	res = best_move_to_object(g, 'C', &(g->player[0]));
	ft_printf("Min distance to collectible: %d\n", res.min_steps);
	ft_printf("target x: %d\n", res.target.x);
	ft_printf("target y %d\n", res.target.y);
	if (res.best_move == MOVE_UP)
		ft_printf("BEST MOVE: MOVE_UP\n");
	else if (res.best_move == MOVE_DOWN)
		ft_printf("BEST MOVE: MOVE_DOWN\n");
	else if (res.best_move == MOVE_LEFT)
		ft_printf("BEST MOVE: MOVE_LEFT\n");
	else if (res.best_move == MOVE_RIGHT)
		ft_printf("BEST MOVE: MOVE_RIGHT\n");
	else if (res.best_move == NONE)
		ft_printf("BEST MOVE: NONE\n");*/

#include "../inc/so_long.h"

static int	init_map_counters(t_game *g)
{
	g->cnt = ft_calloc(1, sizeof(t_counter));
	if (g->cnt == 0)
		return (ALLOC_ERROR);
	g->cnt->players = 0;
	g->cnt->foes = 0;
	g->cnt->exits = 0;
	g->cnt->total_gems = 0;
	g->cnt->taken_gems = 0;
	g->cnt->moves = 0;
	return (IN_PLAY);
}

static int	init_foes(t_game *g, int i, int j)
{
	t_actor	*new_foe;
	int		k;

	k = -1;
	new_foe = ft_calloc(g->cnt->foes + 1, sizeof(t_actor));
	if (!new_foe)
		return (ALLOC_ERROR);
	while (++k < g->cnt->foes)
		new_foe[k] = g->foe[k];
	g->cnt->foes++;
	new_foe[g->cnt->foes - 1].pos.x = i;
	new_foe[g->cnt->foes - 1].pos.y = j;
	g->foe = new_foe;
	return (IN_PLAY);
}

static int	parse_map_counters(t_game *g, char c, int i, int j)
{
	if (c == 'C')
		g->cnt->total_gems++;
	else if (c == 'E')
		g->cnt->exits++;
	else if (c == 'P')
	{
		g->cnt->players++;
		if (g->cnt->players != 1)
			return (MAP_ERROR);
		g->player = ft_calloc(1, sizeof(t_actor));
		if (!g->player)
			return (ALLOC_ERROR);
		g->player->pos.x = i;
		g->player->pos.y = j;
	}
	else if (c == 'F')
		return (init_foes(g, i, j));
	if (c == '0' || c == '1' || c == 'E' || c == 'C' || c == 'P')
		return (IN_PLAY);
	else
		return (MAP_ERROR);
}

static int	parse_map(t_game *g)
{
	int	i;
	int	j;

	if (init_map_counters(g) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	i = -1;
	j = -1;
	while (++j < g->map_y_len)
	{
		while (++i < g->map_x_len)
		{
			g->state = parse_map_counters(g, g->map[j][i], i, j);
			if (((i == 0 || j == 0 || i == g->map_x_len - 1
						|| j == g->map_y_len - 1) && (g->map[j][i] != '1'))
				|| g->state == MAP_ERROR || g->state == ALLOC_ERROR)
				return (g->state);
		}
		i = 0;
	}
	if (g->cnt->players != 1 || g->cnt->exits != 1 || g->cnt->total_gems == 0)
		return (MAP_ERROR);
	return (IN_PLAY);
}

int	init_map(t_game *g, char *file_name)
{
	int			fd;
	int			i;

	i = -1;
	g->map_y_len = get_number_of_lines(file_name);
	if (!g->map_y_len)
		return (MAP_ERROR);
	g->map = ft_calloc(g->map_y_len, sizeof(char *));
	fd = open(file_name, O_RDONLY);
	while (++i < g->map_y_len)
	{
		g->map[i] = get_next_line(fd);
		g->map_x_len = ft_strlen(g->map[i]);
		if (g->map[i][g->map_x_len - 1] == '\n')
			g->map[i][--(g->map_x_len)] = '\0';
		if ((i != 0 && g->map_x_len != (int)ft_strlen(g->map[i - 1]))
			|| g->map_x_len < 3)
			return (MAP_ERROR);
	}
	g->state = parse_map(g);
	if ((best_move_to_object(g, 'C', g->player)).min_steps == -1
			|| (best_move_to_object(g, 'E', g->player)).min_steps == -1)
		return (MAP_ERROR);
	return (IN_PLAY);
}
