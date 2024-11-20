/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:16:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/20 11:42:50 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static inline int	is_key_move(int keysym)
{
	return (keysym == XK_Left || keysym == XK_Right || keysym == XK_Up
		|| keysym == XK_Down || keysym == XK_a || keysym == XK_d
		|| keysym == XK_w || keysym == XK_s);
}

int	on_keypress(int keysym, t_data *data)
{
	if ((data->map->exit.x == data->map->player.x)
		&& (data->map->exit.y == data->map->player.y))
	{
		clean_up(data);
		exit(0);
	}
	if (keysym == XK_Escape)
		on_destroy(data);
	if (is_key_move(keysym))
		move_player(get_direction(keysym), data);
	return (0);
}
