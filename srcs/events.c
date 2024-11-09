/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:16:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/08 20:05:55 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int on_keypress(int keysym, t_data *data)
{
	(void)data;
	ft_printf("Pressed key: %d\\n", keysym);
	if (keysym == XK_Escape)
		on_destroy(data);
	return (0);
}