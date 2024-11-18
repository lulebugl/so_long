/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:31 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/18 16:14:19 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	init_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->map->col * TILE_SIZE,
			data->map->row * TILE_SIZE, "So_long");
	if (!data->win)
		display_err_and_exit("Failed to create window", data);
	data->img.img = mlx_new_image(data->mlx, data->map->col * TILE_SIZE,
			data->map->row * TILE_SIZE);
	if (!data->img.img)
		display_err_and_exit("Failed to create image", data);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
}

void	launch_game(t_data *data)
{
	init_window(data);
	debug_print(data, 0);
	load_textures(data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &on_keypress, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &on_destroy, data);
	render_water(data);
	render_grass(data);
	render_map(data);
	mlx_loop(data->mlx);
}
