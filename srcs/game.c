/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:31 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/15 19:53:52 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// void	render_tiles(t_data *data)
// {

// }

int	surrounded_by_water(int **matrix, int x, int y)
{
	if (matrix[x - 1][y] == WATER)
		return (1);
	if (matrix[x + 1][y] == WATER)
		return (1);
	if (matrix[x][y - 1] == WATER)
		return (1);
	if (matrix[x][y + 1] == WATER)
		return (1);
	return (0);
}

void	object_render(t_data *data)
{
	int		img_width;
	int		img_height;
	t_img	*texture0;
	t_img	*texture;
	int		row;
	int		col;

	row = data->map->row - 1;
	debug_print(data, 0);
	while (row)
	{
		col = data->map->col - 1;
		while (col)
		{
			// if (data->map->matrix[row][col] == '1')
			// {
			// 	texture = get_texture_for_element(data, TREE, row, col);
			// 	mlx_put_image_to_window(data->mlx, data->win, texture, (col - 2)
			// 		* TILE_SIZE * 3, (row - 2)* TILE_SIZE * 3);
			// }
			if (data->map->matrix[row][col] == PLAYER)
			{
				texture0 = mlx_xpm_file_to_image(data->mlx, "assets/tiles/middle.xpm", &img_width, &img_height);
				mlx_put_image_to_window(data->mlx, data->win, texture0, col
					* TILE_SIZE, row * TILE_SIZE);
				texture = mlx_xpm_file_to_image(data->mlx, "assets/tiles/pawn_yellow.xpm", &img_width, &img_height);
				mlx_put_image_to_window(data->mlx, data->win, texture, col
					* TILE_SIZE / 2, row * TILE_SIZE / 2);
			}
			col--;
		}
		row--;
	}
}

void	render_initial_map(t_data *data)
{
	int		img_width;
	int		img_height;
	void	*texture;
	int		row;
	int		col;

	row = -1;
	load_textures(data);
	debug_print(data, 0);
	ft_printf("Starting render_initial_map\n");
	while (++row < data->map->row)
	{
		col = -1;
		while (++col < data->map->col)
		{
			ft_printf("Processing tile at [%d,%d] - Type: %d\n", row, col,
				data->map->matrix[row][col]);
			if (data->map->matrix[row][col] == WATER)
				texture = get_texture_for_element(data, WATER, row, col);
			else
			{
				// if (surrounded_by_water(data->map->matrix, row, col))
				// {
				// 	ft_printf("Tile [%d,%d] is surrounded by water\n", row,
				// 		col);
				// 	texture = get_texture_for_element(data, WATER, row, col);
				// 	mlx_put_image_to_window(data->mlx, data->win, texture, col
				// 		* TILE_SIZE, row * TILE_SIZE);
				// }
				texture = get_texture_for_element(data, EMPTY, row, col);
			}
			mlx_put_image_to_window(data->mlx, data->win, texture, col
				* TILE_SIZE, row * TILE_SIZE);
		}
	}
	ft_printf("Finished render_initial_map\n");
}

void	launch_game(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->map->col * TILE_SIZE,
			data->map->row * TILE_SIZE, "So_long");
	if (!data->win)
		return (display_err_and_exit("Failed to launch window\n.", data));

	// Register key release hook
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &on_keypress, data);

	// Register destroy hook
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &on_destroy, data);
	render_initial_map(data);
	object_render(data);
	// render_game(data);
	mlx_loop(data->mlx);
}