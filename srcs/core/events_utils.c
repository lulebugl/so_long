/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:46:37 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 17:03:58 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	ft_victory(t_data *data)
{
	ft_printf(RESET);
	ft_printf("=================================\n");
	ft_printf("        🏆  VICTORY !!!\n");
	ft_printf("--------------------------------\n");
	ft_printf("    Total moves: %d\n", data->nb_moves);
	ft_printf("    Collectibles left: %d\n", data->map->nb_collectible);
	ft_printf("\n  Press any key to continue...\n\n");
	ft_printf("=================================\n");
	ft_printf(RESET);
}

int	on_destroy(t_data *data)
{
	clean_up(data);
	exit(0);
	return (0);
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
