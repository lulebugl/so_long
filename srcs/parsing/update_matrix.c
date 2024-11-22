/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:43:08 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 21:41:47 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	choose_object(int **matrix, int x, int y)
{
	if (x <= 1)
		return (0);
	if (!is_obstacle(matrix[x][y]))
		return (0);
	if (is_obstacle(matrix[x - 1][y]))
	{
		if (is_obstacle(matrix[x][y - 1]) && is_obstacle(matrix[x][y + 1]))
			return (TREE);
		else
			return (BUSH);
	}
	if (matrix[x - 1][y] == TREE)
		return (TREE);
	return (0);
}

int	update_matrix(t_data *data)
{
	int	**matrix;
	int	x;
	int	y;
	int	elem;

	x = 0;
	matrix = data->map->matrix;
	while (++x < data->map->row - 1)
	{
		y = 0;
		while (++y < data->map->col - 1)
		{
			if (matrix[x][y] == OBSTACLE)
				matrix[x][y] = WATER;
			elem = choose_object(data->map->matrix, x, y);
			if (elem != 0)
				matrix[x][y] = elem;
		}
	}
	return (0);
}
