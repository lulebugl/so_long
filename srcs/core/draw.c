/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:02:06 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 21:59:20 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	draw_top_tree(t_pos player, t_data *data)
{
	if (player.x < data->map->row - 2 \
		&& data->map->matrix[player.x + 2][player.y] == TREE)
	{
		draw_texture(&data->img, data->textures[TEX_TOP_TREE], player.y
			* TILE_SIZE, player.x * TILE_SIZE);
	}
}

static void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	handle_big_tex(t_texture *tex, t_img *img, int start_x, int start_y)
{
	int				x;
	int				y;
	unsigned int	color;

	start_x += tex->offset_x;
	start_y += tex->offset_y;
	y = -1;
	while (++y < tex->height)
	{
		if (start_y + y < 0)
			continue ;
		x = -1;
		while (++x < tex->width)
		{
			color = tex->data[y * tex->width + x];
			if (color != TRANSPARENCY_COLOR)
				draw_pixel(img, start_x + x, start_y + y, color);
		}
	}
}

void	draw_texture(t_img *img, t_texture *tex, int start_x, int start_y)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	if (tex->height > TILE_SIZE || tex->width > TILE_SIZE)
	{
		handle_big_tex(tex, img, start_x, start_y);
		return ;
	}
	while (++y < tex->height)
	{
		x = -1;
		while (++x < tex->width)
		{
			color = tex->data[y * tex->width + x];
			if (color != 0)
				draw_pixel(img, start_x + x, start_y + y, color);
		}
	}
}
