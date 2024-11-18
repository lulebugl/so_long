/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:07:39 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/18 16:26:52 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	set_err_msg(char *msg, t_data *data)
{
	data->err_msg = msg;
}

static void	clean_map(t_map *map)
{
	if (map->matrix)
		free_matrix(map->matrix, map->row);
	free(map);
}

void	cleanup_textures(t_data *data)
{
	int	i;

	i = -1;
	if (!data->textures || !data->textures[0])
		return ;
	while (++i < TEX_COUNT)
	{
		if (data->textures[i])
		{
			if (data->textures[i]->data)
				free(data->textures[i]->data);
			free(data->textures[i]);
			data->textures[i] = NULL;
		}
	}
}
void	clean_up(t_data *data)
{
	if (!data)
		return ;
	if (data->win && data->img.img)
		mlx_destroy_window(data->mlx, data->win);
	if (data->win)
		mlx_destroy_image(data->mlx, data->img.img);
	cleanup_textures(data);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	clean_map(data->map);
}

void	display_err_and_exit(const char *msg, t_data *data)
{
	ft_printf_fd(2, YELLOW);
	ft_printf_fd(2, "Error\n");
	if (!msg)
	{
		if (data->err_msg)
			ft_printf_fd(2, data->err_msg);
	}
	else
		ft_printf_fd(2, "%s", msg, RESET);
	ft_printf_fd(2, RESET);
	clean_up(data);
	exit(EXIT_FAILURE);
}
