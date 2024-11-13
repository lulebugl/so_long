/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:49:54 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/13 13:55:51 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void    debug_print(t_data *data, char *location)
{
    if (!data)
        return ;

    ft_printf("\n========== DEBUG INFO ==========\n");
    if (location)
        ft_printf("Location: %s\n", location);
    ft_printf("\n=== Window Info ===\n");
    ft_printf("Max Row: %d\n", data->max_row);
    ft_printf("Max Col: %d\n", data->max_col);
    ft_printf("MLX Pointer: %p\n", data->mlx);
    ft_printf("Window Pointer: %p\n", data->win);

    if (data->err_msg)
        ft_printf("\n=== Error Message ===\n%s\n", data->err_msg);

    if (data->map)
    {
        ft_printf("\n=== Map Info ===\n");
        ft_printf("Row Count: %d\n", data->map->row);
        ft_printf("Column Count: %d\n", data->map->col);
        ft_printf("Collectibles: %d\n", data->map->nb_collectible);
        ft_printf("Player Position: (%d, %d)\n", 
            data->map->player.x, data->map->player.y);
        ft_printf("Exit Position: (%d, %d)\n", 
            data->map->exit.x, data->map->exit.y);

        // if (data->map->matrix)
        //     print_matrix_debug(data->map->matrix, data->map->row, data->map->col);
    }
    ft_printf("==============================\n\n");
}

void	close_and_free(void *str, int fd)
{
	close(fd);
	free(str);
}

void	print_matrix(int **matrix, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map->row)
	{
		j = -1;
		while (++j < data->map->col)
			ft_printf("%d", matrix[i][j]);
		ft_printf("\n");
	}
}
