/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:45:07 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/18 20:23:30 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	free_matrix(int **matrix, int i)
{
	if (!matrix || !*matrix)
		return ;
	if (!i)
	{
		free(matrix);
		return ;
	}
	while (i--)
		if (matrix[i])
			free(matrix[i]);
	free(matrix);
}



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

int	update_matrix(t_data *data)
{
	int	**matrix;
	int	x;
	int	y;

	x = 0;
	matrix = data->map->matrix;
	while (++x < data->map->row)
	{
		y = 0;
		while (++y < data->map->col)
		{
			if (matrix[x][y] == OBSTACLE)
				data->map->matrix[x][y] = TREE;
			if (data->map->matrix[x - 1][y] && data->map->matrix[x
				- 1][y] == COLLECTIBLE && data->map->matrix[x][y] == OBSTACLE)
				data->map->matrix[x][y] = TRUNK;
		}
	}
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
