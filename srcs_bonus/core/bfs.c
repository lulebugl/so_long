/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:29:36 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 19:11:05 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

static bool	is_valid_move(t_data *data, int **visited, int x, int y)
{
	return (x >= 0 && x < data->map->row && y >= 0 && y < data->map->col
		&& !visited[x][y] && !is_obstacle(data->map->matrix[x][y])
		&& data->map->matrix[x][y] != GOBLIN);
}

/*
** Process a single position in the pathfinding queue
*/
static void	process_position(t_data *data, t_pos current, t_check *check)
{
	if (current.x == data->map->exit.x && current.y == data->map->exit.y)
		check->reached_exit = true;
	if (data->map->matrix[current.x][current.y] == COLLECTIBLE)
		check->collectibles++;
}

/*
** Check adjacent positions and add valid ones to queue
*/
static void	check_adjacents(t_data *data, t_pathfind *pf, t_pos current)
{
	static int	dx[] = {-1, 1, 0, 0};
	static int	dy[] = {0, 0, -1, 1};
	int			i;
	t_pos		new_pos;

	i = -1;
	while (++i < 4)
	{
		new_pos.x = current.x + dx[i];
		new_pos.y = current.y + dy[i];
		if (is_valid_move(data, pf->visited, new_pos.x, new_pos.y))
		{
			pf->queue[*pf->rear] = new_pos;
			(*pf->rear)++;
			pf->visited[new_pos.x][new_pos.y] = true;
		}
	}
}

bool	check_paths_bfs(t_data *data, t_pathfind *pf)
{
	t_pos	current;

	while (*pf->front < *pf->rear)
	{
		current = pf->queue[(*pf->front)++];
		process_position(data, current, pf->check);
		check_adjacents(data, pf, current);
		if (pf->check->reached_exit && pf->check->collectibles == data->map->nb_collectible)
			return (1);
	}
	return (pf->check->reached_exit
		&& pf->check->collectibles == data->map->nb_collectible);
}
