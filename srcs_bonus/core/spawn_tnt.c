/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_tnt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:17:20 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 18:03:21 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

/*
** Uses BFS algorithm for pathfinding
** returns: true if path to exit exists and all collectibles are reachable
*/
bool	has_clear_path(t_data *data, t_pos start)
{
	t_pathfind	pf;
	int			front;
	int			rear;
	t_check		check;
	bool		result;

	pf.visited = create_visited_matrix(data);
	if (!pf.visited)
		return (false);
	pf.queue = malloc(sizeof(t_pos) * (data->map->row * data->map->col));
	if (!pf.queue)
		return (cleanup_pathfinding(pf.visited, NULL, data->map->row), false);
	front = 0;
	rear = 0;
	check = (t_check){false, 0};
	pf.front = &front;
	pf.rear = &rear;
	pf.check = &check;
	pf.queue[rear++] = start;
	pf.visited[start.x][start.y] = true;
	result = check_paths_bfs(data, &pf);
	cleanup_pathfinding(pf.visited, pf.queue, data->map->row);
	return (result);
}

static bool	try_spawn_location(t_data *data, int *empty_spots, int empty_count)
{
	t_texture	*tex;
	int			x;
	int			y;
	int			random_index;

	while (empty_count > 0)
	{
		random_index = rand() % empty_count;
		y = empty_spots[random_index] / data->map->col;
		x = empty_spots[random_index] % data->map->col;
		data->map->matrix[y][x] = GOBLIN;
		if (has_clear_path(data, data->map->player))
		{
			tex = get_texture_for_elem(data, GOBLIN, 0, 0);
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

static void	wandered_too_much(t_data *data)
{
	ft_printf("==========================================\n");
	ft_printf("    ☠️   You Wandered for too long      !!!\n");
	ft_printf("------------------------------------------\n");
	ft_printf("    Total moves: %d\n", data->nb_moves);
	ft_printf("    Collectibles left: %d\n", data->map->nb_collectible);
	ft_printf("\n  Press any key to continue...\n\n");
	ft_printf("==========================================\n");
	clean_up(data);
	exit(0);
}
void	spawn_tnt(t_data *data)
{
	static clock_t	last_spawn = 0;
	clock_t			current_time;
	double			elapsed;
	int				*empty_spots;
	int				empty_count;

	current_time = clock();
	elapsed = (double)(current_time - last_spawn) / CLOCKS_PER_SEC;
	if (elapsed < get_spawn_rate(data))
		return ;
	empty_spots = malloc(sizeof(int) * data->map->row * data->map->col);
	if (!empty_spots)
		return ;
	empty_count = collect_empty_spots(data, empty_spots);
	if (try_spawn_location(data, empty_spots, empty_count))
	{
		free(empty_spots);
		last_spawn = current_time;
	}
	else if (!has_clear_path(data, data->map->player))
	{
		free(empty_spots);
		wandered_too_much(data);
	}
}

