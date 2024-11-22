/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:54:05 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 20:59:04 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

/* Animation related functions */

void	init_sheep_animation(t_data *data)
{
	int i;

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

void	update_sheep_animation(t_data *data)
{
	int				x;
	int				y;
	t_texture		*tex;
	static clock_t	last_spawn = 0;
	clock_t			current_time;
	double			elapsed;

	current_time = clock();
	elapsed = (double)(current_time - last_spawn) / CLOCKS_PER_SEC;
	data->sheep.delay_counter++;
	if (data->sheep.delay_counter >= data->sheep.frame_delay)
	{
		data->sheep.current_frame = (data->sheep.current_frame + 1)
			% data->sheep.frame_count;
		// printf("current frame -> %d\n", data->sheep.current_frame);
		data->sheep.delay_counter = 0;
	}
	// if (elapsed > 1)
	// {
		y = 0;
		while (++y < data->map->row)
		{
			x = 0;
			while (++x < data->map->col)
			{
				if (data->map->matrix[y][x] == COLLECTIBLE)
				{
					// Use the current animation frame for collectibles
					tex = get_texture_for_elem(data, EMPTY, y, x);
					if (tex)
						draw_texture(&data->img, tex, x * TILE_SIZE, y
							* TILE_SIZE);
					draw_texture(&data->img,
						data->sheep.frames[data->sheep.current_frame], x
						* TILE_SIZE, y * TILE_SIZE);
					last_spawn = current_time;
				}
			}
		}
	// }
}
