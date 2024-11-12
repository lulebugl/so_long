/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:00:32 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/12 17:57:41 by llebugle         ###   ########.fr       */
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

void	launch_game(t_data *data)
{
	int		img_width;
	int		img_height;
	int i;
	int j;

	i = -1;
	data->win = mlx_new_window(data->mlx, data->map->col * TILE_SIZE, data->map->row * TILE_SIZE, "So_long");
	if (!data->win)
		return (display_err_and_exit("Failed to launch window\n.", data));
	
	// Register key release hook
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &on_keypress, data);

	// Register destroy hook
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &on_destroy, data);
	
	data->textures[0] = mlx_xpm_file_to_image(data->mlx, GRASS, &img_width, &img_height);
	ft_printf("row : %d\n", data->map->row);
	ft_printf("col : %d\n", data->map->col);
	while (++i < data->map->row)
	{
		j = -1;
		while (++j < data->map->col)
			mlx_put_image_to_window(data->mlx, data->win, data->textures[0], i * TILE_SIZE, j * TILE_SIZE);
	}
	printf("test\n");
	mlx_destroy_window(data->mlx, data->win);
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
	mlx_loop(data.mlx);

    return (0);
}