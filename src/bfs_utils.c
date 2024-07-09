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

void	init_queue(t_queue *q)
{
	q->front = NULL;
	q->rear = NULL;
}

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
	static t_point	invalid = {-1, -1};
	t_node			*temp;
	t_point			pos;

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

void	free_queue(t_queue *q)
{
	while (q->front != NULL)
		dequeue(q);
}
