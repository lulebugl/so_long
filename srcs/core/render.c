/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:47:46 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/17 22:44:32 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	render_water(t_data *data)
{
	int			x;
	int			y;
	t_texture	*tex;

	ft_memset(data->img.addr, 0, data->map->col * TILE_SIZE * data->map->row
		* TILE_SIZE * (data->img.bits_per_pixel / 8));
	y = -1;
	while (++y < data->map->row)
	{
		x = -1;
		while (++x < data->map->col)
		{
			tex = get_texture_for_elem(data, WATER, y, x);
			if (tex)
				draw_texture(&data->img, tex, x * TILE_SIZE, y * TILE_SIZE);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	render_grass(t_data *data)
{
	int			x;
	int			y;
	t_texture	*tex;

	y = -1;
	while (++y < data->map->row)
	{
		x = -1;
		while (++x < data->map->col)
		{
			if (data->map->matrix[y][x] != WATER)
			{
				tex = get_texture_for_elem(data, EMPTY, y, x);
				if (tex)
					draw_texture(&data->img, tex, x * TILE_SIZE, y * TILE_SIZE);
			}
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

static void	erase_player_last_pos(t_pos player, t_data *data)
{
	t_texture	*tex;

	tex = get_texture_for_elem(data, data->map->matrix[player.x][player.y],
			player.x, player.y);
	if (tex)
		draw_texture(&data->img, tex, player.y * TILE_SIZE, player.x
			* TILE_SIZE);
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
			// if (data->map->matrix[y][x] == PLAYER
			// 	&& (data->map->exit.x == data->map->player.x)
			// 	&& (data->map->exit.y == data->map->player.y))
			// {
			// 	tex = get_texture_for_elem(data, EXIT, y, x);
			// 	if (tex)
			// 		draw_texture(&data->img, tex, x * TILE_SIZE, y * TILE_SIZE);
			// 	tex = get_texture_for_elem(data, PLAYER, y, x);
			// 	if (tex)
			// 		draw_texture(&data->img, tex, x * TILE_SIZE, y * TILE_SIZE);
			// 	continue ;
			// }
			if (data->map->matrix[y][x] != WATER
				&& data->map->matrix[y][x] != EMPTY)
				tex = get_texture_for_elem(data, data->map->matrix[y][x], y, x);
			if (tex)
				draw_texture(&data->img, tex, x * TILE_SIZE, y * TILE_SIZE);
		}
	}
	// debug_print(data, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
