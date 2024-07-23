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
	if (c == '0' || c == '1' || c == 'E' || c == 'C' || c == 'P')
		return (IN_PLAY);
	else
		return (MAP_ERROR);
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
			if (((i == 0 || j == 0 || i == g->x_s - 1
						|| j == g->y_s - 1) && (g->map[j][i] != '1'))
				|| g->state == MAP_ERROR || g->state == ALLOC_ERROR)
				return (g->state);
		}
		i = -1;
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
	g->y_s = get_number_of_lines(file_name);
	if (!g->y_s)
		return (MAP_ERROR);
	g->map = ft_calloc(g->y_s, sizeof(char *));
	fd = open(file_name, O_RDONLY);
	while (++i < g->y_s)
	{
		g->map[i] = get_next_line(fd);
		g->x_s = ft_strlen(g->map[i]);
		if (g->map[i][g->x_s - 1] == '\n')
			g->map[i][--(g->x_s)] = '\0';
		if ((i != 0 && g->x_s != (int)ft_strlen(g->map[i - 1])) || g->x_s < 3)
			return (MAP_ERROR);
	}
	g->state = parse_map(g);
	if ((best_move_to_object(g, 'C', g->player)).min_steps == -1
		|| (best_move_to_object(g, 'E', g->player)).min_steps == -1)
		return (MAP_ERROR);
	return (IN_PLAY);
}

void	init_game(t_game *g, int argc, char **argv)
{
	char	*file_name;

	g->state = validate_file_name(argv[1]);
	if (argc != 2 || (argc == 2 && g->state == ARG_ERROR))
	{
		ft_printf("Error\n: Number of arguments or map name is incorrect\n");
		return ;
	}
	g->texture = (t_texture *)malloc(sizeof(t_texture));
	if (!g->texture)
	{
		g->state = ALLOC_ERROR;
		return ;
	}
	file_name = ft_strjoin("./maps/", argv[1]);
	g->state = init_map(g, file_name);
	free(file_name);
	init_mlx(g);
	if (g->state == MAP_ERROR)
		ft_printf("Error\n: Chosen map is invalid, the game is not possible\n");
	else if (g->state == ALLOC_ERROR)
		ft_printf("Error\n: Not enough memory, the game is not possible\n");
	else if (g->state == MLX_ERROR)
		ft_printf("Error\n: MLX lib issue or there are missing textures\n");
	else
		init_hooks(g);
}
