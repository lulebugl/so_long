/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:31 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/17 19:44:56 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	init_window(t_data *data)
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

void	launch_game(t_data *data)
{
	init_window(data);
	debug_print(data, 0);
	load_textures(data);
	// debug_print(data, 0);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &on_keypress, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &on_destroy, data);
	render_water(data);
	render_grass(data);
	render_map(data);
	//render_player(data, data->map->player);
	// mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
}


// int	render_player(t_data *data, t_pos player)
// {
// 	t_texture	*tex;
// 	int			**matrix;

// 	matrix = data->map->matrix;
// 	print_matrix(matrix, data);
// 	print_player_pos(player);
// 	printf("x -> %d\n", player.x);
// 	tex = get_texture_for_element(data, PLAYER, 0, 0);
// 	if (tex)
// 		draw_texture(&data->img, tex, player.y * TILE_SIZE, player.x
// 			* TILE_SIZE);
// 	if (player.x + 1 < data->map->row && matrix[player.x + 1][player.y] == TREE)
// 	{
// 		tex = get_texture_for_element(data, TREE, 0, 0);
// 		if (tex)
// 			draw_texture(&data->img, tex, player.y * TILE_SIZE, (player.x + 1)
// 				* TILE_SIZE);
// 	}
// 	if (player.x + 2 < data->map->row && matrix[player.x + 2][player.y] == TREE)
// 	{
// 		tex = get_texture_for_element(data, TREE, 0, 0);
// 		if (tex)
// 			draw_texture(&data->img, tex, player.y * TILE_SIZE, (player.x + 2)
// 				* TILE_SIZE);
// 	}
// 	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
// 	return (0);
// }


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
// 			if (data->map->matrix[y][x] != WATER
//				&& data->map->matrix[y][x] != EMPTY)
//             	tex = get_texture_for_element(data, data->map->matrix[y][x], y,
//			x);
// 			if (tex)
// 			{
// 				if (data->map->matrix[y][x] == WALL)
// 				{
//                		draw_texture(&data->img, tex, x * TILE_SIZE, y
//			* TILE_SIZE);
// 				}
// 				else
//                		draw_texture(&data->img, tex, x * TILE_SIZE, y
//			* TILE_SIZE);
// 			}
// 			x--;
//         }
// 		y--;
//     }
//     mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
// }