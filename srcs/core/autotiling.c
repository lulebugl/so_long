/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autotiling.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:38:19 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/18 17:44:26 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	get_adjacent_tiles(t_data *data, int x, int y, int *adjacent)
{
	adjacent[0] = 0;
	adjacent[1] = 0;
	adjacent[2] = 0;
	adjacent[3] = 0;
	if (x > 0)
		adjacent[0] = (data->map->matrix[x - 1][y] == WATER);
	if (y < data->map->col - 1)
		adjacent[1] = (data->map->matrix[x][y + 1] == WATER);
	if (x < data->map->row - 1)
		adjacent[2] = (data->map->matrix[x + 1][y] == WATER);
	if (y > 0)
		adjacent[3] = (data->map->matrix[x][y - 1] == WATER);
}

static t_texture_type	get_texture_corner(int *adj)
{
	if (adj[0] && adj[3] && !adj[1] && !adj[2])
		return (TEX_GRASS_TOP_LEFT);
	if (adj[0] && adj[1] && !adj[3] && !adj[2])
		return (TEX_GRASS_TOP_RIGHT);
	if (adj[2] && adj[3] && !adj[1] && !adj[0])
		return (TEX_GRASS_BOTTOM_LEFT);
	if (adj[2] && adj[1] && !adj[3] && !adj[0])
		return (TEX_GRASS_BOTTOM_RIGHT);
	if (adj[0] && !adj[1] && !adj[2] && !adj[3])
		return (TEX_GRASS_TOP);
	if (!adj[0] && adj[1] && !adj[2] && !adj[3])
		return (TEX_GRASS_RIGHT);
	if (!adj[0] && !adj[1] && adj[2] && !adj[3])
		return (TEX_GRASS_BOTTOM);
	if (!adj[0] && !adj[1] && !adj[2] && adj[3])
		return (TEX_GRASS_LEFT);
	return (0);
}

static t_texture_type	get_texture_line(int *adj)
{
	if (adj[0] && adj[2] && !adj[3] && !adj[1])
		return (TEX_GRASS_HM);
	if (!adj[0] && !adj[2] && !adj[3] && adj[1])
		return (TEX_GRASS_HR);
	if (!adj[0] && !adj[2] && adj[3] && !adj[1])
		return (TEX_GRASS_HL);
	if (!adj[0] && !adj[2] && adj[3] && adj[1])
		return (TEX_GRASS_VM);
	if (!adj[0] && adj[2] && !adj[3] && !adj[1])
		return (TEX_GRASS_VB);
	if (adj[0] && !adj[2] && !adj[3] && !adj[1])
		return (TEX_GRASS_VT);
	return (TEX_GRASS_ALL);
}

t_texture_type	check_adjacent(t_data *data, int x, int y)
{
	int 			adjacent[4];
	t_texture_type	texture;

	get_adjacent_tiles(data, x, y, adjacent);
	texture = get_texture_corner(adjacent);
	if (texture)
		return (texture);
	return (get_texture_line(adjacent));
}
