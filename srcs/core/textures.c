/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:00:14 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/21 18:23:13 by llebugle         ###   ########.fr       */
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
		return (free(tex), NULL);
	tex->offset_x = (TILE_SIZE - tex->width) / 2;
	tex->offset_y = TILE_SIZE - tex->height;
	if (tex->height > TILE_SIZE)
		tex->offset_y = -(tex->height - TILE_SIZE);
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bits_per_pixel,
			&tex->img.line_length, &tex->img.endian);
	tex->data = (int *)malloc(sizeof(int) * (tex->width * tex->height));
	if (!tex->data)
	{
		mlx_destroy_image(mlx, tex->img.img);
		return (free(tex), NULL);
	}
	tmp = -1;
	while (++tmp < tex->width * tex->height)
		tex->data[tmp] = ((int *)tex->img.addr)[tmp];
	return (mlx_destroy_image(mlx, tex->img.img), tex);
}

void	load_textures_others(t_data *data)
{
	data->textures[TEX_TREE] = load_texture(data->mlx, TREE_PATH);
	data->textures[TEX_WATER] = load_texture(data->mlx, WATER_PATH);
	data->textures[TEX_COLLECTIBLE] = load_texture(data->mlx, COLLECTIBLE_PATH);
	data->textures[TEX_TRUNK] = load_texture(data->mlx, TREE_TRUNK_PATH);
	data->textures[TEX_PLAYER] = load_texture(data->mlx, PLAYER_PATH);
	data->textures[TEX_EXIT] = load_texture(data->mlx, EXIT_PATH);
	data->textures[TEX_BANNER] = load_texture(data->mlx, BANNER_PATH);
	data->textures[TEX_FOAM] = load_texture(data->mlx, FOAM_PATH);
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
	data->textures[TEX_GRASS_HR] = load_texture(data->mlx, GRASS_HR);
	data->textures[TEX_GRASS_HL] = load_texture(data->mlx, GRASS_HL);
	data->textures[TEX_GRASS_HM] = load_texture(data->mlx, GRASS_HM);
	data->textures[TEX_GRASS_VT] = load_texture(data->mlx, GRASS_VT);
	data->textures[TEX_GRASS_VB] = load_texture(data->mlx, GRASS_VB);
	data->textures[TEX_GRASS_VM] = load_texture(data->mlx, GRASS_VM);
	data->textures[TEX_GRASS_SINGLE] = load_texture(data->mlx, GRASS_SINGLE);
	load_textures_others(data);
	while (++i < TEX_COUNT)
		if (!data->textures[i])
			display_err_and_exit("Failed to load textures", data);
}

t_texture	*get_texture_for_elem(t_data *data, int element, int x, int y)
{
	t_texture_type	tex_type;

	if (element == EMPTY)
	{
		tex_type = check_adjacent(data, x, y);
		return (data->textures[tex_type]);
	}
	if (element == TREE)
		return (data->textures[TEX_TREE]);
	if (element == FOAM)
		return (data->textures[TEX_FOAM]);
	if (element == TRUNK)
		return (data->textures[TEX_TRUNK]);
	if (element == BANNER)
		return (data->textures[TEX_BANNER]);
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
