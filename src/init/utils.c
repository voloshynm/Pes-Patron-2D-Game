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

int	validate_file_name(char *s)
{
	int		len;

	if (s == NULL)
		return (ARG_ERROR);
	len = ft_strlen(s);
	if (len < 4 || ft_strncmp(s + len - 4, ".ber", 4) != 0)
		return (ARG_ERROR);
	return (IN_PLAY);
}

int	file_exists(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

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
