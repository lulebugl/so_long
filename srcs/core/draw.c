/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:02:06 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/16 18:07:44 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_texture(t_img *img, t_texture *tex, int start_x, int start_y)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	if (tex->height > TILE_SIZE || tex->width > TILE_SIZE)
	{
		start_x += tex->offset_x;
		start_y += tex->offset_y;
		while (++y < tex->height)
		{
			// Skip drawing pixels that would be above the tile
			if (start_y + y < 0)
				continue ;
			x = -1;
			while (++x < tex->width)
			{
				// don't need that for now, it shouldn't be possible
				// Skip drawing pixels that would be outside the tile horizontally
				// if (start_x + x < 0 || start_x + x >= img->width)
				// 	continue ;
				color = tex->data[y * tex->width + x];
				if (color != TRANSPARENCY_COLOR)
					draw_pixel(img, start_x + x, start_y + y, color);
			}
		}
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