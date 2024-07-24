/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:34:37 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/07/18 17:34:41 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

static char	*actor_sprite_location(char *actor_name, char *action, char *j_s,
									char *i_s)
{
	char	*result;
	int		len;

	len = 10 + ft_strlen(actor_name) + 1 + ft_strlen(action)
		+ 1 + ft_strlen(j_s) + 1 + ft_strlen(i_s) + 4 + 1;
	result = (char *)malloc(len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, "./sprites/", len);
	ft_strlcat(result, actor_name, len);
	ft_strlcat(result, "/", len);
	ft_strlcat(result, action, len);
	ft_strlcat(result, "/", len);
	ft_strlcat(result, j_s, len);
	ft_strlcat(result, "/", len);
	ft_strlcat(result, i_s, len);
	ft_strlcat(result, ".xpm", len);
	return (result);
}

static char	*item_sprite_location(char *item_name, char *i_s)
{
	char	*result;
	int		len;

	len = 10 + ft_strlen(item_name) + 1 + ft_strlen(i_s) + 4 + 1;
	result = (char *)malloc(len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, "./sprites/", len);
	ft_strlcat(result, item_name, len);
	ft_strlcat(result, "/", len);
	ft_strlcat(result, i_s, len);
	ft_strlcat(result, ".xpm", len);
	return (result);
}

static void	load_actor(t_game *g, void *actor[4][8], char *actor_n
					, char *action)
{
	char	*file_path;
	char	*j_s;
	char	*i_s;
	int		i;
	int		j;

	j = -1;
	while (++j < 4 && g->state != MLX_ERROR)
	{
		i = -1;
		j_s = ft_itoa(j);
		while (++i < 8 && g->state != MLX_ERROR)
		{
			i_s = ft_itoa(i);
			file_path = actor_sprite_location(actor_n, action, j_s, i_s);
			actor[j][i] = mlx_xpm_file_to_image(g->mlx_ptr, file_path,
					&g->sprite_size, &g->sprite_size);
			if (!actor[j][i])
				g->state = MLX_ERROR;
			if (file_path)
				free(file_path);
			free(i_s);
		}
		free(j_s);
	}
}

static void	load_item(t_game *g, void *item_array[64], char *item_name
					, int size)
{
	int		i;
	char	*file_path;
	char	*i_s;

	i = -1;
	while (++i < size)
	{
		i_s = ft_itoa(i);
		file_path = item_sprite_location(item_name, i_s);
		if (file_path != NULL)
		{
			item_array[i] = mlx_xpm_file_to_image(g->mlx_ptr, file_path,
					&g->sprite_size, &g->sprite_size);
			if (item_array[i] == NULL)
			{
				ft_printf("Error: Failed to load image %s\n", file_path);
				g->state = MLX_ERROR;
			}
			free(file_path);
		}
		free(i_s);
	}
}

void	load_textures(t_game *g)
{
	load_item(g, g->texture->floor, "floor", 64);
	load_item(g, g->texture->wall, "wall", 64);
	load_item(g, g->texture->gem, "gem", 8);
	load_item(g, g->texture->exit, "exit", 8);
	load_actor(g, g->texture->player_idle, "player", "idle");
	load_actor(g, g->texture->player_walk, "player", "walk");
	load_actor(g, g->texture->player_hits, "player", "hits");
	load_actor(g, g->texture->player_dead, "player", "dead");
	load_actor(g, g->texture->foe_idle, "foe", "idle");
	load_actor(g, g->texture->foe_walk, "foe", "walk");
	load_actor(g, g->texture->foe_hits, "foe", "hits");
	load_actor(g, g->texture->foe_dead, "foe", "dead");
	if (g->state == MLX_ERROR)
		ft_printf("Error: Failed to load sprite images \n");
	g->texture->keyframe = 0;
	g->texture->frame = 0;
}
