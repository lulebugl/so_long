/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:45:07 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/21 18:22:13 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	put_player(int x, int y, t_data *data, int *row)
{
	data->map->player = (t_pos){x, y};
	data->map->player_prev = (t_pos){x, y};
	row[y] = PLAYER;
}

static int	put_exit(int x, int y, t_data *data, int *row)
{
	data->map->exit = (t_pos){x, y};
	row[y] = EXIT;
}

static int	fill_matrix_row(int *row, char *tab_row, t_data *data, int posx)
{
	int	j;

	j = -1;
	while (tab_row[++j])
	{
		if (tab_row[j] == 'P')
			put_player(posx, j, data, row);
		else if (tab_row[j] == COLLECTIBLE)
		{
			data->map->nb_collectible++;
			row[j] = COLLECTIBLE;
		}
		else if (tab_row[j] == '1' || tab_row[j] == 'T')
			row[j] = TREE;
		else if (tab_row[j] == WATER)
			row[j] = WATER;
		else if (tab_row[j] == TRUNK)
			row[j] = TRUNK;
		else if (tab_row[j] == 'E')
			put_exit(posx, j, data, row);
		else
			row[j] = EMPTY;
	}
	return (0);
}

int	place_object(int **matrix, int x, int y)
{
	if (x <= 1)
		return (0);
	if (!is_obstacle(matrix[x][y]))
		return (0);
	// if (matrix[x - 1][y] == WATER && x == 1)
	// 	return (1);
	if (matrix[x - 1][y] == WATER && is_obstacle(matrix[x - 2][y]))
		return (1);
	return (0);
}

int	choose_object(int **matrix, int x, int y)
{
	if (x <= 1)
		return (0);
	if (!is_obstacle(matrix[x][y]))
		return (0);
	if (matrix[x - 2][y] == WATER && matrix[x - 1][y] == WATER)
		return (1);
	if (matrix[x - 1][y] == TREE)
		return (TREE);
	return (0);
}

int	update_matrix(t_data *data)
{
	int	**matrix;
	int	x;
	int	y;
	int elem;

	x = 0;
	matrix = data->map->matrix;
	while (++x < data->map->row - 1)
	{
		y = 0;
		while (++y < data->map->col - 1)
		{
			if (matrix[x][y] == OBSTACLE)
				matrix[x][y] = WATER;
			elem = place_object(data->map->matrix, x, y);
			if (elem != 0)
				matrix[x][y] = TRUNK;
			if (should_place_tree(matrix, x, y))
				matrix[x][y] = TREE;
		}
	}
	print_matrix(matrix, data);
	return (0);
}

int	create_matrix(char *map, char **tab, t_data *data)
{
	int	i;
	int	**matrix;

	i = -1;
	matrix = (int **)malloc(sizeof(int *) * data->map->row);
	if (!matrix)
		return (set_err_msg(MALLOC_ERROR, data), -1);
	while (++i < data->map->row)
	{
		matrix[i] = malloc(sizeof(int) * ft_strlen(tab[i]));
		if (!matrix[i])
		{
			free_matrix(matrix, i);
			ft_free_tab(tab);
			return (set_err_msg(MALLOC_ERROR, data), -1);
		}
		fill_matrix_row(matrix[i], tab[i], data, i);
	}
	data->map->matrix = matrix;
	free(map);
	ft_free_tab(tab);
	update_matrix(data);
	return (0);
}
