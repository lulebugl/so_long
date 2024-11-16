/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:00:14 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/16 18:49:36 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

t_texture	*load_texture(void *mlx, char *path)
{
	t_texture	*tex;
	int			tmp;

	tex = malloc(sizeof(t_texture));
	if (!tex)
		return (NULL);
	tex->img.img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img.img)
	{
		free(tex);
		return (NULL);
	}
	
	//Calculate offsets based on texture size vs tile size
    tex->offset_x = (TILE_SIZE - tex->width) / 2;  // Center horizontally
    tex->offset_y = TILE_SIZE - tex->height;       // Align to bottom of tile

    // For the tree specifically, adjust vertical position
    if (tex->height > TILE_SIZE)
        tex->offset_y = -(tex->height - TILE_SIZE);  /* Move up by the excess height*/

	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bits_per_pixel,
			&tex->img.line_length, &tex->img.endian);
	tex->data = (int *)malloc(sizeof(int) * (tex->width * tex->height));
	if (!tex->data)
	{
		mlx_destroy_image(mlx, tex->img.img);
		free(tex);
		return (NULL);
	}
	// Copy pixel data
	tmp = -1;
	while (++tmp < tex->width * tex->height)
		tex->data[tmp] = ((int *)tex->img.addr)[tmp];
	mlx_destroy_image(mlx, tex->img.img);
	return (tex);
}

void	load_textures(t_data *data)
{
	int	i;

	i = -1;
	ft_memset(data->textures, 0, sizeof(data->textures));
	data->textures[TEX_GRASS_ALL] = load_texture(data->mlx, GRASS);
	data->textures[TEX_GRASS_TOP] = load_texture(data->mlx, GRASS_TM);
	data->textures[TEX_GRASS_RIGHT] = load_texture(data->mlx, GRASS_MR);
	data->textures[TEX_GRASS_BOTTOM] = load_texture(data->mlx, GRASS_BM);
	data->textures[TEX_GRASS_LEFT] = load_texture(data->mlx, GRASS_ML);
	data->textures[TEX_GRASS_TOP_RIGHT] = load_texture(data->mlx, GRASS_TCR);
	data->textures[TEX_GRASS_BOTTOM_RIGHT] = load_texture(data->mlx, GRASS_BCR);
	data->textures[TEX_GRASS_BOTTOM_LEFT] = load_texture(data->mlx, GRASS_BCL);
	data->textures[TEX_GRASS_TOP_LEFT] = load_texture(data->mlx, GRASS_TCL);
	data->textures[TEX_OBSTACLE] = load_texture(data->mlx, OBSTACLE_PATH);
	data->textures[TEX_WATER] = load_texture(data->mlx, WATER_PATH);
	data->textures[TEX_COLLECTIBLE] = load_texture(data->mlx, GRASS);
	data->textures[TEX_PLAYER] = load_texture(data->mlx, PLAYER_PATH);
	data->textures[TEX_EXIT] = load_texture(data->mlx, EXIT_PATH);
	while (++i < TEX_COUNT)
		if (!data->textures[i])
			display_err_and_exit("Failed to load textures", data);
}

static t_texture_type check_adjacent(t_data *data, int x, int y)
{
    int top = 0;
    int right = 0;
    int bottom = 0;
    int left = 0;

    if (x > 0)
        top = (data->map->matrix[x - 1][y] == WATER);
    if (y < data->map->col - 1)
        right = (data->map->matrix[x][y + 1] == WATER);
    if (x < data->map->row - 1)
        bottom = (data->map->matrix[x + 1][y] == WATER);
    if (y > 0)
        left = (data->map->matrix[x][y - 1] == WATER);

    if (top && left && !right && !bottom)
        return (TEX_GRASS_TOP_LEFT);
    if (top && right && !left && !bottom)
        return (TEX_GRASS_TOP_RIGHT);
    if (bottom && left && !right && !top)
        return (TEX_GRASS_BOTTOM_LEFT);
    if (bottom && right && !left && !top)
        return (TEX_GRASS_BOTTOM_RIGHT);

    if (top && !right && !bottom && !left)
        return (TEX_GRASS_TOP);
    if (!top && right && !bottom && !left)
        return (TEX_GRASS_RIGHT);
    if (!top && !right && bottom && !left)
        return (TEX_GRASS_BOTTOM);
    if (!top && !right && !bottom && left)
        return (TEX_GRASS_LEFT);

    return (TEX_GRASS_ALL);
}

t_texture	*get_texture_for_element(t_data *data, int element, int x, int y)
{
	t_texture_type	tex_type;

	if (element == EMPTY)
	{
		tex_type = check_adjacent(data, x, y);
		return (data->textures[tex_type]);
	}
	if (element == WALL)
		return (data->textures[TEX_OBSTACLE]);
	if (element == COLLECTIBLE)
		return (data->textures[TEX_COLLECTIBLE]);
	if (element == PLAYER)
		return (data->textures[TEX_PLAYER]);
	if (element == EXIT)
		return (data->textures[TEX_EXIT]);
	if (element == WATER)
		return (data->textures[TEX_WATER]);
	return (data->textures[TEX_GRASS_ALL]);
}

