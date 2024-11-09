/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:07:39 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/09 17:07:15 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void set_err_msg(char *msg, t_data *data)
{
	data->err_msg = msg;
}

int on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

void 	display_err_and_exit(const char *msg, t_data *data)
{
	ft_printf_fd(2, "Error\n");
	if (!msg)
		ft_printf_fd(2, data->err_msg);
	else
		perror(msg);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_FAILURE);
}

// void 	display_err_and_exit(t_data *data)
// {
// 	ft_printf_fd(2, "Error\n");
// 	ft_printf_fd(2, "%s", data->err_msg);
// 	ft_printf_fd(2, "%s", data->err_msg);
// 	mlx_destroy_display(data->mlx);
// 	free(data->mlx);
// 	exit(EXIT_FAILURE);
// }