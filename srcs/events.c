/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:16:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/17 21:09:07 by llebugle         ###   ########.fr       */
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

char	*get_direction(int keysym)
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
