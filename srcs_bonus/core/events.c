/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:16:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 16:04:27 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

static inline int	is_key_move(int keysym)
{
	return (keysym == XK_Left || keysym == XK_Right || keysym == XK_Up
		|| keysym == XK_Down || keysym == XK_a || keysym == XK_d
		|| keysym == XK_w || keysym == XK_s);
}

int	on_keypress(int keysym, t_data *data)
{
	if (keysym == XK_e)
	{
		if (data->pause)
			data->pause = false;
		else
			data->pause = true;
	}
	if (keysym == XK_Escape)
		on_destroy(data);
	if ((data->map->exit.x == data->map->player.x)
		&& (data->map->exit.y == data->map->player.y)
		&& data->map->nb_collectible == 0)
	{
		clean_up(data);
		exit(0);
	}
	return (0);
}

int	on_keyrelease(int keysym, t_data *data)
{
	if (is_key_move(keysym))
	{
		data->pause = false;
		move_player(get_direction(keysym), data);
	}
	return (0);
}
