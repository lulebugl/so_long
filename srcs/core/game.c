/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:31 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/18 21:08:29 by llebugle         ###   ########.fr       */
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

int	render_map(t_data *data)
{
	int			x;
	int			y;
	t_texture	*tex;

	y = -1;
	erase_player_last_pos(data->map->player_prev, data);
	while (++y < data->map->row)
	{
		x = -1;
		while (++x < data->map->col)
		{
			tex = NULL;
			if (data->map->matrix[y][x] != WATER
				&& data->map->matrix[y][x] != EMPTY)
				tex = get_texture_for_elem(data, data->map->matrix[y][x], y, x);
			if (tex)
				draw_texture(&data->img, tex, x * TILE_SIZE, y * TILE_SIZE);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	render_banner(data);
	return (0);
}

void	launch_game(t_data *data)
{
	init_window(data);
	load_textures(data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &on_keypress, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &on_destroy, data);
	render_water(data);
	render_foam(data);
	render_grass(data);
	render_map(data);
	mlx_loop(data->mlx);
}
