/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:00:14 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/15 18:51:28 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	load_texture(void **texture, char *path, t_data *data)
{
	int	img_width;
	int	img_height;

	*texture = mlx_xpm_file_to_image(data->mlx, path, &img_width, &img_height);
	if (!*texture)
		display_err_and_exit("Failed to load texture", data);
}

static int check_adjacent(t_data *data, int x, int y)
{
    int is_water_top = 0;
    int is_water_right = 0;
    int is_water_bottom = 0;
    int is_water_left = 0;

    if (x > 0)
        is_water_top = (data->map->matrix[x - 1][y] == WATER);
    if (y < data->map->col - 1)
        is_water_right = (data->map->matrix[x][y + 1] == WATER);
    if (x < data->map->row - 1)
        is_water_bottom = (data->map->matrix[x + 1][y] == WATER);
    if (y > 0)
        is_water_left = (data->map->matrix[x][y - 1] == WATER);

    // Corner cases first
    if (is_water_top && is_water_left && !is_water_right && !is_water_bottom)
        return (GRASS_TOP_LEFT);
    if (is_water_top && is_water_right && !is_water_left && !is_water_bottom)
        return (GRASS_TOP_RIGHT);
    if (is_water_bottom && is_water_left && !is_water_right && !is_water_top)
        return (GRASS_BOTTOM_LEFT);
    if (is_water_bottom && is_water_right && !is_water_left && !is_water_top)
        return (GRASS_BOTTOM_RIGHT);

    // Edge cases
    if (is_water_top && !is_water_right && !is_water_bottom && !is_water_left)
        return (GRASS_TOP);
    if (!is_water_top && is_water_right && !is_water_bottom && !is_water_left)
        return (GRASS_RIGHT);
    if (!is_water_top && !is_water_right && is_water_bottom && !is_water_left)
        return (GRASS_BOTTOM);
    if (!is_water_top && !is_water_right && !is_water_bottom && is_water_left)
        return (GRASS_LEFT);

    return (GRASS_ALL);
}

void    load_texture_grass(t_data *data)
{
    load_texture(&data->textures.empty[GRASS_ALL], GRASS, data);
    load_texture(&data->textures.empty[GRASS_TOP], GRASS_TM, data);
    load_texture(&data->textures.empty[GRASS_RIGHT], GRASS_MR, data);
    load_texture(&data->textures.empty[GRASS_BOTTOM], GRASS_BM, data);
    load_texture(&data->textures.empty[GRASS_LEFT], GRASS_ML, data);
    load_texture(&data->textures.empty[GRASS_TOP_RIGHT], GRASS_TCR, data);
    load_texture(&data->textures.empty[GRASS_BOTTOM_RIGHT], GRASS_BCR, data);
    load_texture(&data->textures.empty[GRASS_BOTTOM_LEFT], GRASS_BCL, data);
    load_texture(&data->textures.empty[GRASS_TOP_LEFT], GRASS_TCL, data);
}

void	load_textures(t_data *data)
{
	load_texture_grass(data);
	load_texture(&data->textures.obstacle, OBSTACLE_PATH, data);
	load_texture(&data->textures.collectible, GRASS, data);
	load_texture(&data->textures.player, PLAYER_PATH, data);
	load_texture(&data->textures.exit, GRASS, data);
	load_texture(&data->textures.water, WATER_PATH, data);
}

void	*get_texture_for_element(t_data *data, int element, int x, int y)
{
	//printf("{%d,%d} -> %d\n", x, y, check_adjacent(data, x, y));
	if (element == EMPTY)
		return (data->textures.empty[check_adjacent(data, x, y)]);
	if (element == TREE)
		return (data->textures.obstacle);
	if (element == COLLECTIBLE)
		return (data->textures.collectible);
	if (element == PLAYER)
		return (data->textures.player);
	if (element == EXIT)
		return (data->textures.exit);
	if (element == WATER)
		return (data->textures.water);
	return (NULL);
}