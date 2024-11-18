/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:47:46 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/18 19:54:13 by llebugle         ###   ########.fr       */
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
