/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:42:14 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 15:17:02 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	update_player_position(t_data *data, t_pos next)
{
	data->map->matrix[data->map->player.x][data->map->player.y] = EMPTY;
	data->map->matrix[next.x][next.y] = PLAYER;
	data->map->player.x = next.x;
	data->map->player.y = next.y;
}

static int	is_valid_move(t_data *data, t_pos next)
{
	if (next.x < 0 || next.x >= data->map->row || next.y < 0
		|| next.y >= data->map->col)
		return (0);
	if (data->map->matrix[next.x][next.y] == WATER)
		return (COLLISION);
	return (!is_obstacle(data->map->matrix[next.x][next.y]));
}

static t_pos	get_next_position(int curr_x, int curr_y, const char *direction)
{
	t_pos	next;

	next.x = curr_x;
	next.y = curr_y;
	if (ft_strncmp(direction, "right", 6) == 0)
		next.y += 1;
	else if (ft_strncmp(direction, "left", 6) == 0)
		next.y -= 1;
	else if (ft_strncmp(direction, "up", 6) == 0)
		next.x -= 1;
	else if (ft_strncmp(direction, "down", 6) == 0)
		next.x += 1;
	return (next);
}

void	ft_drowned(t_data *data, t_pos next)
{
	update_player_position(data, next);
	update_map(data);
	ft_printf("=================================\n");
	ft_printf("    🛟 You've drowned         !!!\n");
	ft_printf("---------------------------------\n");
	ft_printf("    Total moves: %d\n", data->nb_moves);
	ft_printf("    Collectibles left: %d\n", data->map->nb_collectible);
	ft_printf("\n  Press any key to continue...\n\n");
	ft_printf("=================================\n");
	clean_up(data);
	exit(0);
}

void	move_player(const char *direction, t_data *data)
{
	t_pos	next;
	t_map	*map;
	int		ret;

	map = data->map;
	map->player_prev = (t_pos){map->player.x, map->player.y};
	next = get_next_position(map->player.x, map->player.y, direction);
	ret = is_valid_move(data, next);
	if (ret != 0)
	{
		if (ret == COLLISION)
			ft_drowned(data, next);
		data->nb_moves++;
		if (map->matrix[next.x][next.y] == COLLECTIBLE)
			map->nb_collectible--;
		update_player_position(data, next);
		update_map(data);
		if ((map->exit.x == map->player.x) && (map->exit.y == map->player.y)
			&& data->map->nb_collectible == 0)
			ft_victory(data);
	}
}
