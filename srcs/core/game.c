/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:31 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/16 20:28:38 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void    init_window(t_data *data)
{
	debug_print(data, 0);

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

void    render_frame(t_data *data)
{
    int x;
    int y;
    t_texture *tex;

    y = -1;
    while (++y < data->map->row)
    {
        x = -1;
        while (++x < data->map->col)
        {
			tex = NULL;
			if (data->map->matrix[y][x] != WATER && data->map->matrix[y][x] != EMPTY)
				tex = get_texture_for_element(data, data->map->matrix[y][x], y, x);
			if (tex)
			{
				// printf("y - 1: %c\n", data->map->matrix[y - 1][x]);
				// printf("elem : %c\n", data->map->matrix[y][x]);
				if (data->map->matrix[y - 1][x] && data->map->matrix[y - 1][x] == COLLECTIBLE &&
					data->map->matrix[y][x] == WALL)
				{
					tex = get_texture_for_element(data, TRUNK, y, x);
					printf("test\n");
				}
               	draw_texture(&data->img, tex, x * TILE_SIZE, y * TILE_SIZE);
			}
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void    launch_game(t_data *data)
{
    init_window(data);

	debug_print(data, 0);

    load_textures(data);
    
	//debug_print(data, 0);
    mlx_hook(data->win, KeyRelease, KeyReleaseMask, &on_keypress, data);
    mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &on_destroy, data);
    
	render_water(data);
	render_grass(data);

    render_frame(data);
    mlx_loop(data->mlx);
}
// void    render_frame_from_the_end(t_data *data)
// {
//     int x;
//     int y;
//     t_texture *tex;

//     y = data->map->row - 1;
//     while (y)
//     {
//         x = data->map->col - 1;
//         while (x)
//         {
// 			tex = NULL;
// 			if (data->map->matrix[y][x] != WATER && data->map->matrix[y][x] != EMPTY)
//             	tex = get_texture_for_element(data, data->map->matrix[y][x], y, x);
// 			if (tex)
// 			{
// 				if (data->map->matrix[y][x] == WALL)
// 				{
//                		draw_texture(&data->img, tex, x * TILE_SIZE, y * TILE_SIZE);
// 				}
// 				else
//                		draw_texture(&data->img, tex, x * TILE_SIZE, y * TILE_SIZE);
// 			}
// 			x--;
//         }
// 		y--;
//     }
//     mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
// }