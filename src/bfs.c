/*
Breadth-First Search (BFS) is an algorithm for traversing or searching tree or graph data structures. 
It starts at a given node (often called the 'root' in trees) and explores all of its neighboring nodes 
at the present depth level before moving on to nodes at the next depth level. This ensures that the 
algorithm explores all nodes closest to the starting point before exploring nodes further away.

BFS in My Game
In the game, BFS is used to determine if the player can reach all collectibles ('C') on the map, 
and if so, how many steps it takes to get to the nearest collectible. 
Here's how the BFS implementation works:

1. Initialization:
	- Create a queue to keep track of nodes to be explored.
	- Create two arrays, visited and steps, to keep track of visited nodes and the number of steps 
	taken to reach each node.
	- Enqueue the player's starting position and mark it as visited.
2. Processing Nodes:
	- Dequeue a node from the queue and process its neighbors.
	- For each neighbor, if it's a valid move (not a wall or foe) and hasn't been visited yet, 
	mark it as visited, record the steps taken to reach it, and enqueue it.
3. Finding the Minimum Steps:
	- After the BFS completes, iterate over the steps array to find the minimum number of steps needed
	to reach any collectible ('C') that was marked as visited.

	To debug:
	add after line 55:
	printf("Checking if (%d, %d) is valid: %d\n", y, x, result);  // Debug print
	after line 75:
	printf("Visiting (%d, %d), Steps: %d\n", new.y, new.x, steps[new.y][new.x]);  // Debug print
*/
#include "../inc/so_long.h"

static void	init_visited_array(t_game *g, bool visited[g->map_y_len][g->map_x_len],
			int steps[g->map_y_len][g->map_x_len])
{
	int y = 0;
	while (y < g->map_y_len)
	{
		int x = 0;
		while (x < g->map_x_len)
		{
			visited[y][x] = false;
			steps[y][x] = 0;
			x++;
		}
		y++;
	}
}

static bool	is_valid(t_game *g, int y, int x)
{
	bool result;

	result = (x >= 0 && x < g->map_x_len && y >= 0 && y < g->map_y_len &&
		   (g->map[y][x] == '0' || g->map[y][x] == 'C' || g->map[y][x] == 'E'));
	return (result);
}

static void	bfs_process_neighbours(t_game *g, t_queue *q, t_point *current,
			bool visited[g->map_y_len][g->map_x_len],
			int steps[g->map_y_len][g->map_x_len],
			t_direction directions[g->map_y_len][g->map_x_len])
{
	static int			d_x[] = {-1, 1, 0, 0};
	static int			d_y[] = {0, 0, -1, 1};
	static t_direction	dir[] = {MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT};
	int 		i;
	t_point 	new;

	i = -1;
	while (++i < 4)
	{
		new.x = current->x + d_x[i];
		new.y = current->y + d_y[i];
		if (is_valid(g, new.y, new.x) && !visited[new.y][new.x])
		{
			visited[new.y][new.x] = true;
			steps[new.y][new.x] = steps[current->y][current->x] + 1;
			directions[new.y][new.x] = dir[i];
			enqueue(q, new);
		}
	}
}

static void update_result(t_game *g, t_result *result, int steps, t_point target,
				t_direction directions[g->map_y_len][g->map_x_len])
{
	t_point	backtrace;

	if (result->min_steps == -1 || steps < result->min_steps)
	{
		result->min_steps = steps;
		result->target = target;

		backtrace = target;
		while (steps > 1)
		{
			switch (directions[backtrace.y][backtrace.x])
			{
				case MOVE_UP: backtrace.y++; break;
				case MOVE_DOWN: backtrace.y--; break;
				case MOVE_LEFT: backtrace.x++; break;
				case MOVE_RIGHT: backtrace.x--; break;
				default: return;
			}
			steps--;
		}
		result->best_move = directions[backtrace.y][backtrace.x];
	}
}

static t_result	calculate_best_move(t_game *g, bool visited[g->map_y_len][g->map_x_len], 
				char obj, int steps[g->map_y_len][g->map_x_len],
				t_direction directions[g->map_y_len][g->map_x_len])
{
	static	t_result result = { .min_steps = -1, .target = {-1, -1}, .best_move = NONE };
	t_point	point;
	int		min_steps;
	int		i;
	int		j;

	min_steps = -1;
	j = -1;
	while (++j < g->map_y_len)
	{
		i = -1;
		while (++i < g->map_x_len)
		{
			if (g->map[j][i] == obj && visited[j][i])
			{
				point.x = i;
				point.y = j;
				update_result(g, &result, steps[j][i], point, directions);
			}
			
		}
	}
	return (result);
}

t_result	best_move_to_object(t_game *g, char obj, t_actor *actor)
{
	t_queue		q;
	t_point		current;
	bool		visited[g->map_y_len][g->map_x_len];
	int			steps[g->map_y_len][g->map_x_len];
	t_direction	directions[g->map_y_len][g->map_x_len];

	init_queue(&q);
	init_visited_array(g, visited, steps);
	enqueue(&q, actor->pos);
	visited[actor->pos.y][actor->pos.x] = true; 
	while (q.front != NULL)
	{
		current = dequeue(&q);
		bfs_process_neighbours(g, &q, &current, visited, steps, directions);
	}
	free_queue(&q);
	return (calculate_best_move(g, visited,	obj, steps, directions));
}