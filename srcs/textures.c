/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:00:14 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/15 16:31:59 by llebugle         ###   ########.fr       */
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

static int	check_adjacent(t_data *data, int x, int y)
{
	int	top;
	int	right;
	int	bottom;
	int	left;

	top = 1;
	right = 1;
	bottom = 1;
	left = 1;
	if (x > 0)
		top = !is_obstacle(data->map->matrix[x - 1][y]);
	if (y < data->map->col - 1)
		right = !is_obstacle(data->map->matrix[x][y + 1]);
	if (x < data->map->row - 1)
		bottom = !is_obstacle(data->map->matrix[x + 1][y]);
	if (y > 0)
		left = !is_obstacle(data->map->matrix[x][y - 1]);
	if (!top && !right && !bottom && !left)
		return (GRASS_ALL);
	if (!top && !bottom && !left && right)
		return (GRASS_RIGHT);
	if (!top && !bottom && left && !right)
		return (GRASS_LEFT);
	if (!top && bottom && !left && !right)
		return (GRASS_BOTTOM);
	if (top && !bottom && !left && !right)
		return (GRASS_TOP);
	if (!top && !right && bottom && left)
		return (GRASS_BOTTOM_LEFT);
	if (!top && right && bottom && !left)
		return (GRASS_BOTTOM_RIGHT);
	if (top && !right && !bottom && left)
		return (GRASS_TOP_LEFT);
	if (top && right && !bottom && !left)
		return (GRASS_TOP_RIGHT);
	if (!top && !bottom && left && right)
		//return (GRASS_HORIZONTAL);
		return (GRASS_ALL);
	if (top && !right && bottom && !left)
		return (GRASS_ALL);
		//return (GRASS_VERTICAL);
	return (GRASS_ALL);
	//return (GRASS_SINGLE);
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
	load_texture(&data->textures.player, GRASS, data);
	load_texture(&data->textures.exit, GRASS, data);
	load_texture(&data->textures.water, WATER_PATH, data);
}

void	*get_texture_for_element(t_data *data, int element, int x, int y)
{
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