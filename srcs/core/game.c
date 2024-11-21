/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:31 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/21 20:22:32 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	init_window(t_data *data)
{
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

int	render_obstacles(t_data *data)
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

void	draw_top_tree(t_pos player, t_data *data)
{
	if (player.x < data->map->row - 2 && data->map->matrix[player.x + 2][player.y] == TREE)
	{
		draw_texture(&data->img, data->textures[TEX_TOP_TREE], player.y * TILE_SIZE, player.x
			* TILE_SIZE);
	}
}
void	erase_player_last_pos(t_pos player, t_data *data)
{
	t_texture	*tex;

	tex = get_texture_for_elem(data, data->map->matrix[player.x][player.y],
			player.x, player.y);
	if (tex)
		draw_texture(&data->img, tex, player.y * TILE_SIZE, player.x
			* TILE_SIZE);
	draw_top_tree(player, data);
}

int	render_map(t_data *data)
{
	int			x;
	int			y;
	t_texture	*tex;
	t_pos		player;

	y = data->map->player.y;
	x = data->map->player.x;
	erase_player_last_pos(data->map->player_prev, data);
	tex = get_texture_for_elem(data, PLAYER, y, x);
	if (tex)
		draw_texture(&data->img, tex, y * TILE_SIZE, x * TILE_SIZE);
	draw_top_tree(data->map->player, data);
	y = data->map->exit.y;
	x = data->map->exit.x;
	tex = get_texture_for_elem(data, EXIT, y, x);
	if (tex)
		draw_texture(&data->img, tex, y * TILE_SIZE, x * TILE_SIZE);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	render_banner(data);
	return (0);
}

void	launch_game(t_data *data)
{
	init_window(data);
	load_textures(data);
	mlx_hook(data->win, KeyPress, KeyReleaseMask, &on_keypress, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &on_destroy, data);
	render_water(data);
	render_foam(data);
	render_grass(data);
	render_obstacles(data);
	render_map(data);
	// mlx_loop_hook(data->win, &move_player, data);
	mlx_loop(data->mlx);
}
