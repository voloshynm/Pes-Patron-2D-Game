/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:42:19 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/07/09 19:42:21 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	enqueue(t_queue *q, t_point pos)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->pos = pos;
	new_node->next = NULL;
	if (q->front == NULL)
	{
		q->front = new_node;
		q->rear = new_node;
	}
	else
	{
		q->rear->next = new_node;
		q->rear = new_node;
	}
}

t_point	dequeue(t_queue *q)
{
	t_point	invalid;
	t_point	pos;
	t_node	*temp;

	invalid.x = -1;
	invalid.y = -1;
	if (q->front == NULL)
		return (invalid);
	temp = q->front;
	pos = temp->pos;
	q->front = q->front->next;
	if (q->front == NULL)
		q->rear = NULL;
	free(temp);
	return (pos);
}

static void	**allocate_2d_array(int rows, int cols, size_t elem_size)
{
	void	**array;
	int		i;
	int		j;

	array = ft_calloc(rows, sizeof(void *));
	i = -1;
	while (++i < rows)
	{
		array[i] = malloc(cols * elem_size);
		if (!array[i])
		{
			j = -1;
			while (++j < i)
				free(array[j]);
			free(array);
			return (NULL);
		}
	}
	return (array);
}

t_bfs_state	*init_bfs_state(int rows, int cols)
{
	t_bfs_state	*state;
	int			y;
	int			x;

	state = ft_calloc(1, sizeof(t_bfs_state));
	state->map_y_len = rows;
	state->map_x_len = cols;
	state->visited = (bool **)allocate_2d_array(rows, cols, sizeof(bool));
	state->steps = (int **)allocate_2d_array(rows, cols, sizeof(int));
	state->directions = (t_dir **)allocate_2d_array(rows, cols, sizeof(t_dir));
	if (!state->visited || !state->steps || !state->directions)
		free_bfs_state(state);
	y = -1;
	while (++y < rows)
	{
		x = -1;
		while (++x < cols)
		{
			state->visited[y][x] = false;
			state->steps[y][x] = 0;
		}
	}
	return (state);
}

void	free_bfs_state(t_bfs_state *state)
{
	int	i;

	if (!state)
		return ;
	i = -1;
	while (state->visited && ++i < state->map_y_len)
		free(state->visited[i]);
	if (state->visited)
		free(state->visited);
	i = -1;
	while (state->steps && ++i < state->map_y_len)
		free(state->steps[i]);
	if (state->steps)
		free(state->steps);
	i = -1;
	while (state->directions && ++i < state->map_y_len)
		free(state->directions[i]);
	if (state->directions)
		free(state->directions);
	free(state);
}
