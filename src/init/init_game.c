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

#include "../inc/so_long.h"

static char	*check_args(t_game *g, int argc, char **argv)
{
	char	*file_name;

	if (argc != 2)
	{
		printf("Error\n: Number of arguments is incorrect\n");
		g->state = ARG_ERROR;
		return (NULL);
	}
	g->state = validate_file_name(argv[1]);
	if (g->state == ARG_ERROR)
	{
		printf("Error\n: Map name is incorrect\n");
		return (NULL);
	}
	file_name = ft_strjoin("./maps/", argv[1]);
	if (!file_exists(file_name))
	{
		printf("Error\n: Map file does not exist\n");
		free(file_name);
		g->state = ARG_ERROR;
		return (NULL);
	}
	return (file_name);
}

static int	verify_map(t_game *g, char *file_name)
{
	int			fd;
	int			i;

	i = -1;
	g->y_s = get_number_of_lines(file_name);
	if (!g->y_s)
		return (MAP_ERROR);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ARG_ERROR);
	g->map = (char **)ft_calloc(g->y_s, sizeof(char *));
	while (++i < g->y_s)
	{
		g->map[i] = get_next_line(fd);
		g->x_s = ft_strlen(g->map[i]);
		if (g->map[i][g->x_s - 1] == '\n')
			g->map[i][--(g->x_s)] = '\0';
		if ((i != 0 && g->x_s != (int)ft_strlen(g->map[i - 1])) || g->x_s < 3)
			g->state = MAP_ERROR;
	}
	return (g->state);
}

static int	is_alloc_error(t_game *g)
{
	if (!g->texture || g->state == ALLOC_ERROR)
	{
		g->state = ALLOC_ERROR;
		printf("Error\n: Not enough memory, the game is not possible\n");
		free_game(g);
		return (1);
	}
	return (0);
}

int	init_map(t_game *g, char *file_name)
{
	g->state = IN_PLAY;
	g->state = verify_map(g, file_name);
	if (g->state == MAP_ERROR || g->state == ARG_ERROR)
		return (g->state);
	g->state = parse_map(g);
	if (g->state == MAP_ERROR
		|| (best_move_to_object(g, 'C', g->player)).min_steps == -1
		|| (best_move_to_object(g, 'E', g->player)).min_steps == -1)
	{
		free_map(g);
		g->state = MAP_ERROR;
	}
	return (g->state);
}

void	init_game(t_game *g, int argc, char **argv)
{
	char	*file_name;

	file_name = check_args(g, argc, argv);
	if (!file_name)
		return ;
	g->state = init_map(g, file_name);
	free(file_name);
	if (g->state == MAP_ERROR)
	{
		printf("Error\n: Chosen map is invalid, the game is not possible\n");
		free_plot(g);
		return ;
	}
	g->texture = (t_texture *)malloc(sizeof(t_texture));
	if (is_alloc_error(g))
		return ;
	init_mlx(g);
	if (g->state == MLX_ERROR)
	{
		printf("Error\n: MLX lib issue or there are missing textures\n");
		free_game(g);
		return ;
	}
	init_hooks(g);
}
