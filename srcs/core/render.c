/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:47:46 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/20 10:31:51 by llebugle         ###   ########.fr       */
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

	y = 0;
	while (++y < data->map->row)
	{
		x = 0;
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

void	render_foam(t_data *data)
{
	int			x;
	int			y;
	int			adj[4];
	t_texture	*tex;

	y = 0;
	while (++y < data->map->row - 1)
	{
		x = 0;
		while (++x < data->map->col - 1)
		{
			if (data->map->matrix[y][x] != WATER)
			{
				get_adjacent_tiles(data, y, x, adj);
				if (adj[0] == 1 || adj[1] == 1 || adj[2] == 1 || adj[3] == 1)
				{
					tex = get_texture_for_elem(data, FOAM, 0, 0);
					if (tex)
						draw_texture(&data->img, tex, x * TILE_SIZE, y
							* TILE_SIZE + 10);
				}
			}
		}
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	}
}

void	render_banner(t_data *data)
{
	t_texture	*tex;
	char		*tmp;
	char		*msg;
	int			x;
	int			y;

	tex = get_texture_for_elem(data, BANNER, 0, 0);
	if (tex)
		draw_texture(&data->img, tex, 96, (data->map->row - 1) * TILE_SIZE);
	tmp = ft_itoa(data->nb_moves);
	if (!tmp)
		return ;
	msg = ft_strjoin("Moves: ", tmp);
	free(tmp);
	if (!msg)
		return ;
	x = 64;
	y = (data->map->row - 1) * TILE_SIZE;
	mlx_string_put(data->mlx, data->win, x, y + 36, 0x000000, msg);
	mlx_string_put(data->mlx, data->win, x + 1, y + 36, 0x000000, msg);
	mlx_string_put(data->mlx, data->win, x, y + 37, 0x000000, msg);
	free(msg);
}
