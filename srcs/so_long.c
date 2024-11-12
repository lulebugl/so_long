/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:00:32 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/12 14:32:24 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void data_init(t_data *data)
{
	data->max_col = 0;
	data->max_row = 0;
	data->err_msg = NULL;
	data->win = NULL;
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		display_err_and_exit(MALLOC_ERROR, data);
	data->map->matrix = 0;
	data->map->col = 0;
	data->map->row = 0;
	data->map->nb_collectible = 0;
}

int main(int ac, char **av)
{
	t_data	data;
	int		img_width;
	int		img_height;

	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data_init(&data);
	parse_arguments(ac, av, &data);

	ft_printf("sizex : %d\n", data.map->row);
	ft_printf("sizey : %d\n", data.map->col);
	//data.map->row = 20;
	//data.map->col = 30;
	
	//current
	if (!solve(&data))
		display_err_and_exit(NULL, &data);

	data.win = mlx_new_window(data.mlx, data.map->col * TILE_SIZE, data.map->row * TILE_SIZE, "So_long");

	if (!data.win)
		return (free(data.mlx), 1);
	
	// Register key release hook
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &on_keypress, &data);

	// Register destroy hook
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
	
	data.textures[0] = mlx_xpm_file_to_image(data.mlx, GRASS, &img_width, &img_height);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 0 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 1 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 2 * TILE_SIZE);

	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 3 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 4 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 5 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 6 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 7 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 8 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 9 * TILE_SIZE);
	mlx_loop(data.mlx);
    return (0);
}