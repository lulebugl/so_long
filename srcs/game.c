/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:31 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/15 21:03:45 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
    printf("test\n");
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
        &data->img.line_length, &data->img.endian);
}

void    render_frame(t_data *data)
{
    int x;
    int y;
    t_texture *tex;

    // Clear the image
    ft_memset(data->img.addr, 0, data->map->col * TILE_SIZE * data->map->row 
        * TILE_SIZE * (data->img.bits_per_pixel / 8));
    y = -1;
	debug_print(data, 0);
    while (++y < data->map->row)
    {
        x = -1;
        while (++x < data->map->col)
        {
            tex = get_texture_for_element(data, data->map->matrix[y][x], y, x);
			printf("%p\n", data->img.img);
			if (tex)
                draw_texture(&data->img, tex, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	printf("test1220\n");
}

void    launch_game(t_data *data)
{
    init_window(data);

	debug_print(data, 0);

    load_textures(data);
    
	//debug_print(data, 0);
    mlx_hook(data->win, KeyRelease, KeyReleaseMask, &on_keypress, data);
    mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &on_destroy, data);
    
    render_frame(data);
    mlx_loop(data->mlx);
}