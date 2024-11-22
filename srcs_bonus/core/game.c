/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:31 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 14:51:03 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

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

void	draw_top_tree(t_pos player, t_data *data)
{
	if (player.x < data->map->row - 2 && data->map->matrix[player.x
		+ 2][player.y] == TREE)
	{
		draw_texture(&data->img, data->textures[TEX_TOP_TREE], player.y
			* TILE_SIZE, player.x * TILE_SIZE);
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

int	update_map(t_data *data)
{
	int			x;
	int			y;
	t_texture	*tex;
	t_pos		player;

	x = data->map->player.x;
	y = data->map->player.y;
	erase_player_last_pos(data->map->player_prev, data);
	draw_texture(&data->img, data->textures[TEX_PLAYER], y * TILE_SIZE, x
		* TILE_SIZE);
	draw_top_tree(data->map->player, data);
	x = data->map->exit.x;
	y = data->map->exit.y;
	draw_texture(&data->img, data->textures[TEX_EXIT], y * TILE_SIZE, x
		* TILE_SIZE);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	render_banner(data);
	return (0);
}

double get_spawn_rate(t_data *data)
{
    int area = data->map->row * data->map->col;
    if (area > 600)
        return 0.1;
    else if (area > 200)
        return (1.0 / log2(area) * 0.3);
    else
        return 3.0 / log2(area);
}

// function create_mushroom
// function spawn_armor
// function delete_mushroom
// function delete_armor

void spawn_mushroom(t_data *data)
{
    static clock_t last_spawn = 0;
    clock_t current_time;
    double elapsed;
    t_texture *tex;
    // int empty_count = 0;
    int random_spot;
    int x;
    int y;

    current_time = clock();
    elapsed = (double)(current_time - last_spawn) / CLOCKS_PER_SEC;
    
	if (elapsed >= get_spawn_rate(data))
    {
        // First count empty tiles
        // y = -1;
        // while (++y < data->map->row)
        // {
        //     x = -1;
        //     while (++x < data->map->col)
        //         if (data->map->matrix[y][x] == EMPTY)
        //             empty_count++;
        // }
        
        // if (empty_count > 0)
        //{
            // Pick a random empty tile
            random_spot = rand() % (data->map->col * data->map->row);
            
            // Find that specific empty tile
            y = -1;
            while (++y < data->map->row)
            {
                x = -1;
                while (++x < data->map->col)
                {
                    if (data->map->matrix[y][x] == EMPTY)
                    {
                        if (random_spot == 0)
                        {
                            tex = get_texture_for_elem(data, TRUNK, 0, 0);
                            if (tex)
                            {
                                draw_texture(&data->img, tex, x * TILE_SIZE, y * TILE_SIZE);
                                data->map->matrix[y][x] = TRUNK;  // Update matrix
                            }
                            mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
                            last_spawn = current_time;
                            return;
                        }
                        random_spot--;
                    }
                }
            }
        //}
        last_spawn = current_time;
    }
}

int	game_loop(t_data *data)
{
	spawn_mushroom(data);
	update_map(data);
	return (0);
}

void	launch_game(t_data *data)
{
	init_window(data);
	load_textures(data);
	srand(time(NULL));
	mlx_hook(data->win, KeyPress, KeyPressMask, &on_keypress, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &on_keyrelease, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &on_destroy, data);
	render_water(data);
	render_foam(data);
	render_grass(data);
	render_obstacles(data);
	update_map(data);
	mlx_loop_hook(data->mlx, &game_loop, data);
	mlx_loop(data->mlx);
}
