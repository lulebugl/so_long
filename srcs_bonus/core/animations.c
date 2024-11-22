/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:54:05 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 21:34:39 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	init_sheep_animation(t_data *data)
{
	int	i;

	data->sheep.frames[0] = load_texture(data->mlx, "assets/sheep1.xpm");
	data->sheep.frames[1] = load_texture(data->mlx, "assets/sheep2.xpm");
	data->sheep.frames[2] = load_texture(data->mlx, "assets/sheep3.xpm");
	data->sheep.frames[3] = load_texture(data->mlx, "assets/sheep4.xpm");
	data->sheep.frames[4] = load_texture(data->mlx, "assets/sheep5.xpm");
	data->sheep.frames[5] = load_texture(data->mlx, "assets/sheep6.xpm");
	data->sheep.current_frame = 0;
	data->sheep.frame_count = SHEEP_FRAMES;
	data->sheep.frame_delay = 180;
	data->sheep.delay_counter = 0;
	i = -1;
	while (++i < SHEEP_FRAMES)
		if (!data->sheep.frames[i])
			display_err_and_exit("Failed to load foam animation frames", data);
}

static void	draw_sheep(t_data *data, int current_frame)
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
			if (data->map->matrix[y][x] == COLLECTIBLE)
			{
				tex = get_texture_for_elem(data, EMPTY, y, x);
				if (tex)
					draw_texture(&data->img, tex, x * TILE_SIZE, y * TILE_SIZE);
				draw_texture(&data->img, data->sheep.frames[current_frame], x
					* TILE_SIZE, y * TILE_SIZE);
			}
		}
	}
}

void	update_sheep_animation(t_data *data)
{
	int	curr;

	curr = data->sheep.current_frame;
	data->sheep.delay_counter++;
	if (data->sheep.delay_counter >= data->sheep.frame_delay)
	{
		data->sheep.current_frame = (curr + 1) % data->sheep.frame_count;
		data->sheep.delay_counter = 0;
	}
	draw_sheep(data, curr);
}
