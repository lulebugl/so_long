/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_tnt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:17:20 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 16:23:46 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

static bool is_valid_move(t_data *data, int **visited, int x, int y)
{
    return (x >= 0 && x < data->map->row && 
            y >= 0 && y < data->map->col && 
            !visited[x][y] && 
            !is_obstacle(data->map->matrix[x][y]));
}

/*
** Process the BFS queue to check paths to exit and collectibles
** Returns: true if valid path exists to exit and all collectibles
*/
static bool check_paths(t_data *data, t_check *check, int **visited, 
    t_pos *queue, int *front, int *rear)
{
    static int dx[] = {-1, 1, 0, 0};
    static int dy[] = {0, 0, -1, 1};
    t_pos   current;
    int     i;
    int     new_x;
    int     new_y;

    while (*front < *rear)
    {
        current = queue[(*front)++];
        if (current.x == data->map->exit.x && current.y == data->map->exit.y)
            check->reached_exit = true;
        if (data->map->matrix[current.x][current.y] == COLLECTIBLE)
            check->collectibles++;
        i = -1;
        while (++i < 4)
        {
            new_x = current.x + dx[i];
            new_y = current.y + dy[i];
            if (is_valid_move(data, visited, new_x, new_y))
            {
                queue[*rear] = (t_pos){new_x, new_y};
                (*rear)++;
                visited[new_x][new_y] = true;
            }
        }
    }
    return (check->reached_exit && check->collectibles == data->map->nb_collectible);
}

// Part 3: pathfinding.c
/*
** Checks if there's a valid path from start to exit and all collectibles
** Uses BFS algorithm for pathfinding
** Returns: true if path exists to exit and all collectibles are reachable
*/
bool has_clear_path(t_data *data, t_pos start)
{
    static int dx[] = {-1, 1, 0, 0};
    static int dy[] = {0, 0, -1, 1};
    int    **visited;
    t_pos   *queue;
    t_check check;
    int     front;
    int     rear;

    visited = create_visited_matrix(data);
    if (!visited)
        return (false);
    queue = malloc(sizeof(t_pos) * (data->map->row * data->map->col));
    if (!queue)
    {
        cleanup_pathfinding(visited, NULL, data->map->row);
        return (false);
    }
    check = (t_check){false, 0};
    front = 0;
    rear = 0;
    queue[rear++] = start;
    visited[start.x][start.y] = true;
    if (check_paths(data, &check, visited, queue, &front, &rear))
        return (true);
    return (false);
}

static bool try_spawn_location(t_data *data, int *empty_spots, int empty_count)
{
    t_texture   *tex;
    int         x;
    int         y;
    int         random_index;

    while (empty_count > 0)
    {
        random_index = rand() % empty_count;
        y = empty_spots[random_index] / data->map->col;
        x = empty_spots[random_index] % data->map->col;
        data->map->matrix[y][x] = TRUNK;
        if (has_clear_path(data, data->map->player))
        {
            tex = get_texture_for_elem(data, TRUNK, 0, 0);
            if (tex)
                draw_texture(&data->img, tex, x * TILE_SIZE, y * TILE_SIZE);
            mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
            return (true);
        }
        data->map->matrix[y][x] = EMPTY;
        empty_spots[random_index] = empty_spots[--empty_count];
    }
    return (false);
}

void spawn_tnt(t_data *data)
{
    static clock_t  last_spawn = 0;
    clock_t         current_time;
    double          elapsed;
    int             empty_spots[data->map->row * data->map->col];
    int             empty_count;

    current_time = clock();
    elapsed = (double)(current_time - last_spawn) / CLOCKS_PER_SEC;
    if (elapsed < get_spawn_rate(data))
        return ;
    empty_count = collect_empty_spots(data, empty_spots);
    if (try_spawn_location(data, empty_spots, empty_count))
        last_spawn = current_time;
}
