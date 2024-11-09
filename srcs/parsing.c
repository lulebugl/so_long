/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:48:23 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/09 18:50:04 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// to implement later to play fullscreen
// if (av[2] && (!ft_strncmp(av[2], "fullscreen", 11)))
// {
// 	mlx_get_screen_size(data.mlx, &(data.map->col), &(data.map->row));
// 	data.map->row /= TILE_SIZE;
// 	data.map->col /= TILE_SIZE;
// }

void	check_arguments(int ac, char **av, t_data *data)
{
	int len;
	
	if (ac < 2)
		display_err_and_exit("The map is missing.\n", data);
	len = ft_strlen(av[1]);
	if (!ft_strnstr(&av[1][len - 4], ".ber", 4))
		display_err_and_exit(WRONG_EXTENSION, data);
}

int parse_arguments(int ac, char **av, t_data *data)
{
	check_arguments(ac, av, data);
	mlx_get_screen_size(data->mlx, &(data->max_col), &(data->max_row));
	ft_printf("max_row : %d\n", data->max_row);
	ft_printf("max_col : %d\n", data->max_col);
	if (read_map(av[1], data) != 0)
		display_err_and_exit(NULL, data);
	return (0);
}
