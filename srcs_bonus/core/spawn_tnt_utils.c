/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_tnt_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:49:14 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 16:23:28 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

#include "../../includes/so_long_bonus.h"

// returns: Time in seconds between spawns
double get_spawn_rate(t_data *data)
{
    int area;

    area = data->map->row * data->map->col;
    if (area > 600)
        return (0.1);
    else if (area > 300)
        return (0.5 / log2(area) * 0.3);
    return (2.0 / log2(area));
}

int collect_empty_spots(t_data *data, int *empty_spots)
{
    int empty_count;
    int x;
    int y;

    empty_count = 0;
    y = 0;
    while (++y < data->map->row)
    {
        x = 0;
        while (++x < data->map->col)
        {
            if (data->map->matrix[y][x] == EMPTY)
                empty_spots[empty_count++] = y * data->map->col + x;
        }
    }
    return (empty_count);
}

void cleanup_pathfinding(int **visited, t_pos *queue, int row)
{
    int i;

    i = -1;
    while (++i < row)
        free(visited[i]);
    free(visited);
    free(queue);
}