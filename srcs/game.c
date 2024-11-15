/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:31 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/15 16:42:26 by llebugle         ###   ########.fr       */
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

void	render_initial_map(t_data *data)
{
	int		img_width;
	int		img_height;
	void	*texture;
	int		i;
	int		j;

	i = -1;
	printf("test\n");
	load_textures(data);
	printf("test\n");

	while (++i < data->map->row)
	{
		j = -1;
		while (++j < data->map->col)
		{
			if (data->map->matrix[i][j] == WATER)
				texture = get_texture_for_element(data, WATER, i, j);
			else
			{
				// if (surrounded_by_water(data->map->matrix, i, j))
				// 	mlx_put_image_to_window(data->mlx, data->win,
				// 		get_texture_for_element(data, WATER, i, j), j
				// 		* TILE_SIZE, i * TILE_SIZE);
				// //texture = get_texture_for_element(data, EMPTY, i, j);
				// texture = get_texture_for_element(data, GRASS_BOTTOM_LEFT, i, j);
				texture = mlx_xpm_file_to_image(data->mlx, GRASS, &img_width, &img_height);
			}
			mlx_put_image_to_window(data->mlx, data->win, texture, j
				* TILE_SIZE, i * TILE_SIZE);
		}
	}
}

// void	render_game(t_data *data)
// {
// 	int		img_width;
// 	int		img_height;
// 	void	*texture;
// 	int		i;
// 	int		j;

// 	i = -1;
// 	// ft_printf_fd(1, "row : %d\n", data->map->row);
// 	// ft_printf("col : %d\n", data->map->col);
// 	while (++i < data->map->row)
// 	{
// 		j = -1;
// 		while (++j < data->map->col)
// 		{
// 			printf("tests\n");
// 			texture = get_texture_for_element(data, data->map->matrix[i][j]);
// 			mlx_put_image_to_window(data->mlx, data->win, texture, j
// 				* TILE_SIZE, i * TILE_SIZE);
// 		}
// 	}
// }

void	launch_game(t_data *data)
{
	debug_print(data, 0);
	data->win = mlx_new_window(data->mlx, data->map->col * TILE_SIZE,
			data->map->row * TILE_SIZE, "So_long");
	if (!data->win)
		return (display_err_and_exit("Failed to launch window\n.", data));


	// Register key release hook
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &on_keypress, data);

	// Register destroy hook
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &on_destroy, data);
	debug_print(data, 0);
	render_initial_map(data);
	// render_game(data);
	mlx_loop(data->mlx);
}