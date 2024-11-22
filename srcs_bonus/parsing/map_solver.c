/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:45:57 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 15:40:52 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

int	**create_visited_matrix(t_data *data)
{
	int	**visited;
	int	i;

	visited = (int **)malloc(sizeof(int *) * data->map->row);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < data->map->row)
	{
		visited[i] = (int *)calloc(data->map->col, sizeof(int));
		if (!visited[i])
		{
			free_matrix(visited, i);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

static inline bool	is_valid_position(t_data *data, t_pos pos)
{
	return (pos.x >= 0 && pos.x < data->map->row && pos.y >= 0
		&& pos.y < data->map->col);
}

static void	flood_fill(t_data *data, int **visited, t_pos pos, int *collectible)
{
	if (!is_valid_position(data, pos) || visited[pos.x][pos.y])
		return ;
	if (is_obstacle(data->map->matrix[pos.x][pos.y]))
		return ;
	visited[pos.x][pos.y] = 1;
	if (data->map->matrix[pos.x][pos.y] == COLLECTIBLE)
		(*collectible)++;
	flood_fill(data, visited, (t_pos){pos.x + 1, pos.y}, collectible);
	flood_fill(data, visited, (t_pos){pos.x - 1, pos.y}, collectible);
	flood_fill(data, visited, (t_pos){pos.x, pos.y + 1}, collectible);
	flood_fill(data, visited, (t_pos){pos.x, pos.y - 1}, collectible);
}

int	is_map_solvable(t_data *data)
{
	int		**visited;
	int		collectibles;
	bool	can_reach_exit;

	visited = create_visited_matrix(data);
	if (!visited)
		return (set_err_msg(MALLOC_ERROR, data), 0);
	collectibles = 0;
	flood_fill(data, visited, data->map->player, &collectibles);
	can_reach_exit = visited[data->map->exit.x][data->map->exit.y];
	free_matrix(visited, data->map->row);
	if (!can_reach_exit)
		return (set_err_msg(INVALID_EXIT, data), 0);
	if (collectibles != data->map->nb_collectible)
		return (set_err_msg(INVALID_PATH, data), 0);
	return (1);
}
