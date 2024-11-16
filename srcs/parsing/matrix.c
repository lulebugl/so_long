/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:45:07 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/15 15:03:17 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void free_matrix(int **matrix, int i)
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

static int	fill_matrix_row(int *row, char *tab_row, t_data *data, int posx)
{
	int	j;

	j = 0;
	while (tab_row[j])
	{
		if (tab_row[j] == 'P')
		{
			data->map->player.x = posx;
			data->map->player.y = j;
			row[j] = PLAYER;
		}
		else if (tab_row[j] == 'C')
		{
			data->map->nb_collectible++;	
			row[j] = COLLECTIBLE;
		}
		else if (tab_row[j] == '1')
			row[j] = WALL;
		else if (tab_row[j] == WATER)
			row[j] = WATER;
		else if (tab_row[j] == 'E')
		{
			data->map->exit.x = posx;
			data->map->exit.y = j;
			row[j] = EXIT;
		}
		else
			row[j] = EMPTY;
		j++;
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
	print_matrix(data->map->matrix, data);
	free(map);
	ft_free_tab(tab);
	return (0);
}