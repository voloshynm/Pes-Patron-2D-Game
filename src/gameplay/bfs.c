/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:42:08 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/07/09 19:42:14 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Breadth-First Search (BFS) is an algorithm for traversing or searching tree or 
graph data structures. It starts at a given node (often called the 'root' in 
trees) and explores all of its neighboring nodes at the present depth level 
before moving on to nodes at the next depth level. This ensures that the algo
rithm explores all nodes closest to the starting point before exploring nodes
further away.

BFS in My Game
In the game, BFS is used to determine if the player can reach all collectibles
('C') on the map, and if so, how many steps it takes to get to the nearest 
collectible. Here's how the BFS implementation works:

1. Initialization:
	- Create a queue to keep track of nodes to be explored.
	- Create two arrays, visited and steps, to keep track of visited nodes 
	and the number of steps taken to reach each node.
	- Enqueue the player's starting position and mark it as visited.
2. Processing Nodes:
	- Dequeue a node from the queue and process its neighbors.
	- For each neighbor, if it's a valid move (not a wall or foe) and hasn't
	been visited yet, mark it as visited, record the steps taken to reach it,
	and enqueue it.
3. Finding the Minimum Steps:
	- After the BFS completes, iterate over the steps array to find the min
	number of steps needed to reach any collectible ('C') marked as visited.

	To debug:
	after line 85:
printf("Visiting (%d, %d), Steps: %d\n", new.y, new.x, steps[new.y][new.x]);
	after line 101
			ft_printf("steps %d\n", steps);
			ft_printf("backtrace.x: %d\n", backtrace.x);
			ft_printf("backtrace.y: %d\n", backtrace.y);
			if (state->directions[backtrace.y][backtrace.x] == MOVE_UP)
				ft_printf("BT BEST MOVE: MOVE_UP\n");
			else if (state->directions[backtrace.y][backtrace.x] == MOVE_DOWN)
				ft_printf("BT BEST MOVE: MOVE_DOWN\n");
			else if (state->directions[backtrace.y][backtrace.x] == MOVE_LEFT)
				ft_printf("BT BEST MOVE: MOVE_LEFT\n");
			else if (state->directions[backtrace.y][backtrace.x] == MOVE_RIGHT)
				ft_printf("BT BEST MOVE: MOVE_RIGHT\n");
			else if (state->directions[backtrace.y][backtrace.x] == NONE)
				ft_printf("BT BEST MOVE: NONE");

*/
#include "../../inc/so_long.h"

static void	bfs_process_neighbours(t_game *g, t_queue *q, t_point *cur,
			t_bfs_state *state)
{
	static int		d_x[] = {-1, 1, 0, 0};
	static int		d_y[] = {0, 0, -1, 1};
	static t_dir	dir[] = {MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN};
	int				i;
	t_point			new;

	i = -1;
	while (++i < 4)
	{
		new.x = cur->x + d_x[i];
		new.y = cur->y + d_y[i];
		if ((new.x >= 0 && new.x < g->x_s && new.y >= 0
				&& new.y < g->y_s && !state->visited[new.y][new.x])
			&& (g->map[new.y][new.x] != '1'))
		{
			state->visited[new.y][new.x] = true;
			state->steps[new.y][new.x] = state->steps[cur->y][cur->x] + 1;
			state->directions[new.y][new.x] = dir[i];
			enqueue(q, new);
		}
	}
}

static void	update_result(t_result *result, int steps, t_point target,
				t_bfs_state *state)
{
	t_point	backtrace;

	if (result->min_steps == -1 || steps < result->min_steps)
	{
		result->min_steps = steps;
		result->target = target;
		backtrace = target;
		while (steps > 1)
		{
			if (state->directions[backtrace.y][backtrace.x] == MOVE_UP)
				backtrace.y++;
			else if (state->directions[backtrace.y][backtrace.x] == MOVE_DOWN)
				backtrace.y--;
			else if (state->directions[backtrace.y][backtrace.x] == MOVE_LEFT)
				backtrace.x++;
			else if (state->directions[backtrace.y][backtrace.x] == MOVE_RIGHT)
				backtrace.x--;
			steps--;
		}
		result->best_move = state->directions[backtrace.y][backtrace.x];
	}
}

static t_result	calculate_best_move(t_game *g, t_bfs_state *state, char obj)
{
	t_point		point;
	int			i;
	int			j;
	t_result	result;

	result.best_move = NONE;
	result.target.x = -1;
	result.target.y = -1;
	result.min_steps = -1;
	j = -1;
	while (++j < g->y_s)
	{
		i = -1;
		while (++i < g->x_s)
		{
			if (g->map[j][i] == obj && state->visited[j][i])
			{
				point.x = i;
				point.y = j;
				update_result(&result, state->steps[j][i], point, state);
			}
		}
	}
	return (result);
}

t_result	best_move_to_object(t_game *g, char obj, t_actor *actor)
{
	t_queue		q;
	t_point		current;
	t_bfs_state	*state;
	t_result	result;

	q.front = NULL;
	q.rear = NULL;
	state = init_bfs_state(g->y_s, g->x_s);
	enqueue(&q, actor->pos);
	state->visited[actor->pos.y][actor->pos.x] = true;
	while (q.front != NULL)
	{
		current = dequeue(&q);
		bfs_process_neighbours(g, &q, &current, state);
	}
	while (q.front != NULL)
		dequeue(&q);
	result = calculate_best_move(g, state, obj);
	free_bfs_state(state);
	return (result);
}
