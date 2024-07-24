/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:16:40 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/07/02 18:16:41 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"
/* Debugging function:
int	print_map(t_game *g)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	ft_printf ("\n");
	while (++j < g->y_s)
	{
		while (++i < g->x_s)
		{
			ft_printf ("%c", g->map[j][i]);
		}
		ft_printf ("\n");
		i = -1;
	}
	ft_printf ("\n");
	return (IN_PLAY);
}
*/
int	get_number_of_lines(char *file_name)
{
	int		cnt;
	int		fd;
	char	*str;

	cnt = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ARG_ERROR);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		cnt++;
		free(str);
	}
	close(fd);
	return (cnt);
}

int	init_map_counters(t_game *g)
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

static int	validate_file_name(char *s)
{
	int		len;

	if (s == NULL)
		return (ARG_ERROR);
	len = ft_strlen(s);
	if (len < 4 || ft_strncmp(s + len - 4, ".ber", 4) != 0)
		return (ARG_ERROR);
	return (IN_PLAY);
}

static int	file_exists(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

char	*check_args(t_game *g, int argc, char **argv)
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
