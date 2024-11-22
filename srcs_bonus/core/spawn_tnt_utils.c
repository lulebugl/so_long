/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_tnt_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:49:14 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 15:52:44 by llebugle         ###   ########.fr       */
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

bool is_valid_move(t_data *data, int **visited, int x, int y)
{
    return (x >= 0 && x < data->map->row && 
            y >= 0 && y < data->map->col && 
            !visited[x][y] && 
            !is_obstacle(data->map->matrix[x][y]));
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