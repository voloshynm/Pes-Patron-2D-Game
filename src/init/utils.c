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

int	validate_file_name(char *s)
{
	int		len;

	len = ft_strlen(s);
	if (len < 4)
		return (ARG_ERROR);
	if (ft_strncmp(s + len - 4, ".ber", 4) != 0)
		return (ARG_ERROR);
	return (IN_PLAY);
}
