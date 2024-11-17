/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:23:41 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/17 19:15:16 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void 	print_player_pos(t_pos player)
{
	ft_printf("Player Position: (%d, %d)\n", player.x, player.y);
}
void	debug_print(t_data *data, char *location)
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
	// if (data->err_msg)
	// 	ft_printf("\n=== Error Message ===\n%s\n", data->err_msg);
	if (data->map)
	{
		ft_printf("\n=== Map Info ===\n");
		ft_printf("Row Count: %d\n", data->map->row);
		ft_printf("Column Count: %d\n", data->map->col);
		//ft_printf("window size: %dx%d\n", data->map->row, data->map->col);
		ft_printf("Collectibles: %d\n", data->map->nb_collectible);
		ft_printf("Player Position: (%d, %d)\n", data->map->player.x,
			data->map->player.y);
		ft_printf("Exit Position: (%d, %d)\n", data->map->exit.x,
			data->map->exit.y);
		ft_printf("\n=============Matrix==========\n\n");
		print_matrix(data->map->matrix, data);
	}
	ft_printf("==============================\n\n");

}
