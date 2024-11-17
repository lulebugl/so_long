/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:00:32 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/17 18:37:49 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	data_init(t_data *data)
{
	data->max_col = 0;
	data->max_row = 0;
	data->err_msg = NULL;
	data->win = NULL;
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		display_err_and_exit(MALLOC_ERROR, data);
	data->map->matrix = 0;
	data->map->col = 0;
	data->map->row = 0;
	data->map->nb_collectible = 0;
}

int main(int ac, char **av)
{
	t_data	data;

	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data_init(&data);
	parse_arguments(ac, av, &data);
	if (!is_map_solvable(&data))
		display_err_and_exit(NULL, &data);
	launch_game(&data);
    return (0);
}