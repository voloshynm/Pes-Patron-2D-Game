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

int	validate_file_name(char *s)
{
	char	*ext;
	int		len;

	len = ft_strlen(s);
	if (len < 4)
		return (ARG_ERROR);
	if (ft_strncmp(s + len - 4, ".ber", 4) != 0)
		return (ARG_ERROR);
	return (IN_PLAY);
}

int	parse_map (t_game *game)
{

}

int	init_map(t_game *game, char *file_name)
{
	int		fd;
	int		i;

	i = 1;
	fd = open(file_name, O_RDONLY);
	game->map[0] = get_next_line(fd);
	if (game->map[0] == NULL)
		return (MAP_ERROR);
	game->map_x_len = ft_strlen(game->map[0]);
	game->map_y_len = 0;
	while(1)
	{
		game->tmp_line = get_next_line(fd);
		if (game->tmp_line == NULL && game->map_x_len != 0)
			break;
		game->map_x_len = ft_strlen(game->tmp_line);
		if (game->map_x_len != ft_strlen(game->map[i - 1]) || game->map_x_len < 3)
			return (MAP_ERROR);
		game->map[i++] = game->tmp_line;
		game->map_y_len++;
	}
	parse_map(&game);
	return (IN_PLAY);
}


void	init_game(t_game *game, int argc, char **argv)
{
	char	*file_name;

	file_name = argv[1];
	if (argc != 2 || (argc == 2 && validate_file_name(file_name) == ARG_ERROR))
	{
		ft_printf("ERROR: number of arguments or map name is incorrect");
		game->state == ARG_ERROR;
	}
	game->state == init_map(game->map, file_name);
	if (validate_map(game->map) == MAP_ERROR)
	{
		ft_printf("ERROR: selected map is invalid, game is not possible");
		game->state == MAP_ERROR;
	}
}

int main(int argc, char **argv)
{
	t_game  game;
	
	init_game(&game, argc, argv);
	while(game.state == IN_PLAY)
	{
		mlx_hook(game->mlx_ptr, KeyPress, KeyPressMask, &on_keypress, data);
		mlx_hook(game->win_ptr, DestroyNotify, StructureNotifyMask,
			&game_destroy, data);
		mlx_loop_hook(game->mlx_ptr, &refresh, data);
		mlx_loop(game->mlx_ptr);
	}
	free_game(&game);
}
