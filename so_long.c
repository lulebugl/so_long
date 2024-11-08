/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:00:32 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/08 13:22:29 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(void)
{
	t_data	data;
	int		img_width;
	int		img_height;

	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, 1980, 1020, "Hello world!");
	if (!data.win)
		return (free(data.mlx), 1);
	// Register key release hook
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &on_keypress, &data);

	// Register destroy hook
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
	data.textures[0] = mlx_xpm_file_to_image(data.mlx, GRASS, &img_width, &img_height);
	ft_printf("width : %d\n", img_width);
	ft_printf("height : %d\n", img_height);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 0 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 1 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 2 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 3 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 4 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 5 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 6 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 7 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 8 * TILE_SIZE);
	mlx_put_image_to_window(data.mlx, data.win, data.textures[0], 1, 9 * TILE_SIZE);
	mlx_loop(data.mlx);
    return (0);
}