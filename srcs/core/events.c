/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:16:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/21 20:25:04 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static inline int	is_key_move(int keysym)
{
	return (keysym == XK_Left || keysym == XK_Right || keysym == XK_Up
		|| keysym == XK_Down || keysym == XK_a || keysym == XK_d
		|| keysym == XK_w || keysym == XK_s);
}

// int on_keypress(int keysym, t_data *data)
// {
//     if (keysym == XK_Escape)
//         on_destroy(data);
//     else if (keysym == XK_Left || keysym == XK_a)
//         data->keys.left = 1;
//     else if (keysym == XK_Right || keysym == XK_d)
//         data->keys.right = 1;
//     else if (keysym == XK_Up || keysym == XK_w)
//         data->keys.up = 1;
//     else if (keysym == XK_Down || keysym == XK_s)
//         data->keys.down = 1;
//     return (0);
// }

// int on_keyrelease(int keysym, t_data *data)
// {
//     if (keysym == XK_Left || keysym == XK_a)
//         data->keys.left = 0;
//     else if (keysym == XK_Right || keysym == XK_d)
//         data->keys.right = 0;
//     else if (keysym == XK_Up || keysym == XK_w)
//         data->keys.up = 0;
//     else if (keysym == XK_Down || keysym == XK_s)
//         data->keys.down = 0;
//     return (0);
// }

int	on_keypress(int keysym, t_data *data)
{
	if ((data->map->exit.x == data->map->player.x)
		&& (data->map->exit.y == data->map->player.y)
		&& data->map->nb_collectible == 0)
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
