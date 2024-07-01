#include "../inc/so_long.h"

static void	init_map_counters(t_game *g)
{
	g->cnt->players = 0;
	g->cnt->foes = 0;
	g->cnt->exits = 0;
	g->cnt->total_gems = 0;
	g->cnt->taken_gems = 0;
	g->cnt->moves = 0;
}

static int	init_foes(t_game *g, int i, int j)
{
	t_actor	*new_foe;
	int		k;

	k = -1;
	new_foe = ft_calloc(g->cnt->foes + 1, sizeof(t_actor));
	if(!new_foe)
		return (ALLOC_ERROR);
	while (k++ < g->cnt->foes)
		new_foe[k] = g->foe[k];
	g->cnt->foes++;
	new_foe[g->cnt->foes - 1].pos.x = i;
	new_foe[g->cnt->foes - 1].pos.y = j;
	g->foe = new_foe;
	return (IN_PLAY);
}

static int parse_map_counters(t_game *g, char c, int i, int j)
{
	if (c == 'C')
		g->cnt->total_gems++;
	else if (c == 'E')
		g->cnt->exits++;
	else if (c == 'P')
	{
		g->cnt->players++;
		if (g->cnt->players != 1)
			return(MAP_ERROR);
		g->player = ft_calloc(1, sizeof(t_actor));
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
	int j;

	init_map_counters(g);
	i = -1;
	j = -1;
	while (j++ < g->map_y_len)
	{
		while (i++ < g->map_x_len)
		{
			g->state = parse_map_counters(g, g->map[j][i], i , j);
			if (((i == 0 || j == 0 || i == g->map_x_len - 1
					|| j == g->map_y_len - 1) && (g->map[j][i] != '1'))
				|| g->state == MAP_ERROR)
				return (MAP_ERROR);
			else if (g->state == ALLOC_ERROR)
				return (ALLOC_ERROR);
		}
	}
	if (g->cnt->players != 1 || g->cnt->exits != 1 || g->cnt->total_gems == 0)
		return (MAP_ERROR);
	return (IN_PLAY);
}

int	init_map(t_game *g, char *file_name)
{
	int		fd;
	int		i;

	i = -1;
	g->map_y_len = get_number_of_lines(file_name);
	if (g->map_y_len == NULL)
		return (MAP_ERROR);
	g->map = ft_calloc(g->map_y_len, sizeof(char *));
	fd = open(file_name, O_RDONLY);
	while(i++ < g->map_y_len)
	{
		g->map[i] = get_next_line(fd);
		g->map_x_len = ft_strlen(g->map[i]);
		if (g->map[i][g->map_x_len-- - 1] == '\n')
			g->map[i][g->map_x_len] == '\0';
		/*if (g->tmp_line == NULL && g->map_x_len != 0)
			break;*/
		if ((i != 0 && g->map_x_len != ft_strlen(g->map[i - 1]))
			|| g->map_x_len < 3)
			return (MAP_ERROR);
	}
	parse_map(g);
//	validate_winability(&g);
	return (IN_PLAY);
}

int	get_number_of_lines(char *file_name)
{
	int		cnt;
	int		fd;
	char	*str;

	cnt = 0;
	fd = open(file_name, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break;
		cnt++;
		free(str);
	}
	close(fd);
	return (cnt);
}