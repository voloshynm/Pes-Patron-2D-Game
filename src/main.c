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
#include "../../inc/so_long.h"

static int	validate_file_name(char *s)
{
	int		len;

	len = ft_strlen(s);
	if (len < 4)
		return (ARG_ERROR);
	if (ft_strncmp(s + len - 4, ".ber", 4) != 0)
		return (ARG_ERROR);
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
	file_name = ft_strjoin("./maps/", argv[1]);
	g->state = init_map(g, file_name);
	init_mlx(g);
	free(file_name);
	if (g->state == MAP_ERROR)
		ft_printf("Error\n: Chosen map is invalid, the game is not possible\n");
	else if (g->state == ALLOC_ERROR)
		ft_printf("Error\n: Not enough memory, the game is not possible\n");
	else if (g->state == MLX_ERROR)
		ft_printf("Error\n: MLX lib issue or there are missing textures\n");
	else
		init_hooks(g);
}

int	main(int argc, char **argv)
{
	t_game	g;

	init_game(&g, argc, argv);
	while (g.state == IN_PLAY)
		update_game(g);
	free_game(&g);
}
