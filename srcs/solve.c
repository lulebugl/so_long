/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:45:57 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/12 15:51:39 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	**create_visited_matrix(t_data *data);
static int	count_collectibles(t_map *map);

static void	flood_fill(t_data *data, int **visited, int x, int y,
		int *collectibles)
{
	// Check if position is out of bounds or is a wall
	if (x < 0 || x >= data->map->row || y < 0 || y >= data->map->col
		|| data->map->matrix[x][y] == OBSTACLE || visited[x][y])
		return ;
	visited[x][y] = 1;
	if (data->map->matrix[x][y] == COLLECTIBLE)
		(*collectibles)++;
	flood_fill(data, visited, x + 1, y, collectibles);
	flood_fill(data, visited, x - 1, y, collectibles);
	flood_fill(data, visited, x, y + 1, collectibles);
	flood_fill(data, visited, x, y - 1, collectibles);
}

int	solve(t_data *data)
{
	int	**visited;
	int	collectibles;

	visited = create_visited_matrix(data);
	if (!visited)
		return (set_err_msg(MALLOC_ERROR, data), 0);
	collectibles = 0;
	// ft_printf("\nNeed to find %d collectibles\n", data->map->nb_collectible);
	// ft_printf("Starting at position (%d, %d)\n", data->map->player.y,
	// 	data->map->player.x);
	flood_fill(data, visited, data->map->player.x, data->map->player.y,
		&collectibles);
	print_matrix(visited, data);
	if (visited[data->map->exit.x][data->map->exit.y] != 1)
	{
		free_matrix(visited, data->map->row);
		return (data->err_msg = INVALID_EXIT, 0);
	}
	free_matrix(visited, data->map->row);
	if (collectibles != data->map->nb_collectible)
		return (data->err_msg = INVALID_PATH, 0);
	return (1);
}

static int	count_collectibles(t_map *map)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->col)
			if (map->matrix[i][j++] == COLLECTIBLE)
				count++;
		i++;
	}
	return (count);
}

static int	**create_visited_matrix(t_data *data)
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
