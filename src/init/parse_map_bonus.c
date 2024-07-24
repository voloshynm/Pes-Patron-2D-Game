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
	new_foe[g->cnt->foes].pos.x = i;
	new_foe[g->cnt->foes].pos.y = j;
	new_foe[g->cnt->foes].dir = NONE;
	new_foe[g->cnt->foes].d = -1;
	new_foe[g->cnt->foes].action = -1;
	if (g->cnt->foes > 0)
		free(g->foe);
	g->foe = new_foe;
	g->cnt->foes++;
	return (IN_PLAY);
}

static int	parse_map_counters(t_game *g, char c, int i, int j)
{
	if (c != '0' && c != '1' && c != 'E' && c != 'C' && c != 'P' && c != 'F')
		return (MAP_ERROR);
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
		g->player->dir = NONE;
		g->player->d = -1;
		g->player->action = -1;
	}
	else if (c == 'F')
		return (init_foes(g, i, j));
	return (IN_PLAY);
}

int	parse_map(t_game *g)
{
	int	i;
	int	j;

	if (init_map_counters(g) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	i = -1;
	j = -1;
	while (++j < g->y_s)
	{
		while (++i < g->x_s)
		{
			g->state = parse_map_counters(g, g->map[j][i], i, j);
			if (((i == 0 || j == 0 || i == g->x_s - 1 || j == g->y_s - 1)
					&& (g->map[j][i] != '1')) || g->state == MAP_ERROR)
				return (MAP_ERROR);
		}
		i = -1;
	}
	if (g->cnt->players != 1 || g->cnt->exits != 1 || g->cnt->total_gems < 1)
		g->state = MAP_ERROR;
	return (g->state);
}
