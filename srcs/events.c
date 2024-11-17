/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:16:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/17 20:09:51 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	on_destroy(t_data *data)
{
	clean_up(data);
	exit(0);
	return (0);
}

static inline int	is_key_move(int keysym)
{
	return (keysym == XK_Left || keysym == XK_Right || keysym == XK_Up
		|| keysym == XK_Down || keysym == XK_a || keysym == XK_d
		|| keysym == XK_w || keysym == XK_s);
}

static t_pos	get_next_position(int curr_x, int curr_y, char *direction)
{
	t_pos	next;

	next.x = curr_x;
	next.y = curr_y;
	if (direction == "right")
		next.y += 1;
	else if (direction == "left")
		next.y -= 1;
	else if (direction == "up")
		next.x -= 1;
	else if (direction == "down")
		next.x += 1;
	return (next);
}

static char	*get_direction(int keysym)
{
	if (keysym == XK_Left || keysym == XK_a)
		return ("left");
	if (keysym == XK_Right || keysym == XK_d)
		return ("right");
	if (keysym == XK_Up || keysym == XK_w)
		return ("up");
	if (keysym == XK_Down || keysym == XK_s)
		return ("down");
	return (0);
}

static int	is_valid_move(t_data *data, t_pos next)
{
	if (next.x < 0 || next.x >= data->map->row || next.y < 0
		|| next.y >= data->map->col)
		return (0);
	if (data->map->matrix[next.x][next.y] == EXIT && data->map->nb_collectible > 0)
		return (0);
	return (!is_obstacle(data->map->matrix[next.x][next.y]));
}

static void	update_player_position(t_data *data, t_pos next)
{
	if (data->map->matrix[next.x][next.y] == EXIT)
	{
		data->map->matrix[data->map->player.x][data->map->player.y] = EMPTY;
		data->map->matrix[next.x][next.y] = PLAYER;
		data->map->player.x = next.x;
		data->map->player.y = next.y;
	}
	else
	{
		data->map->matrix[data->map->player.x][data->map->player.y] = EMPTY;
		data->map->matrix[next.x][next.y] = PLAYER;
		data->map->player.x = next.x;
		data->map->player.y = next.y;
	}
}

void	move_player(char *direction, t_data *data)
{
	t_pos	next;

	data->map->player_prev = (t_pos){data->map->player.x, data->map->player.y};
	next = get_next_position(data->map->player.x, data->map->player.y,
			direction);
	if (is_valid_move(data, next))
	{
		update_player_position(data, next);
		ft_printf("New Position: (%d, %d)\n", data->map->player.x,
			data->map->player.y);
		render_map(data);
	}
}

int	on_keypress(int keysym, t_data *data)
{
	(void)data;
	ft_printf("Pressed key: %d\n", keysym);
	if (keysym == XK_Escape)
		on_destroy(data);
	if (is_key_move(keysym))
		move_player(get_direction(keysym), data);
	return (0);
}

// void move_player(char *direction, t_data *data)
// {
//     int x;
//     int y;
//     int **matrix;

//     matrix = data->map->matrix;
//     x = data->map->player.x;
//     y = data->map->player.y;
//     ft_printf("Player Position: (%d, %d)\n", data->map->player.x,
//	data->map->player.y);
//     if (direction == "right")
//     {
//         ft_printf("elem y + 1: %c\n", matrix[x][y + 1]);
//         if (!is_obstacle(matrix[x][y + 1]))
//         {
//             data->map->matrix[x][y] = EMPTY;
//             data->map->matrix[x][y + 1] = PLAYER;
//             data->map->player.y++;
//             ft_printf("Player Position: (%d, %d)\n", data->map->player.x,
//	data->map->player.y);
//         }
//     }
// }