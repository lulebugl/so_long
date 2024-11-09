/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:42:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/09 17:27:57 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_arguments(int ac, char **av, t_data *data)
{
	int len;
	
	if (ac < 2)
		display_err_and_exit("The map is missing.\n", data);
	len = ft_strlen(av[1]);
	if (!ft_strnstr(&av[1][len - 4], ".ber", 4))
		display_err_and_exit(WRONG_EXTENSION, data);
}

int	validate_map_content(char *map, t_data *data)
{
	int	i;

	i = 0;
	if (ft_strlen(map) < 3)
		return (set_err_msg(EMPTY_LINES, data), 1);
	if (*map == '\n' || !(*map))
		return (set_err_msg(EMPTY_LINES, data), 1);
	while (map[i] && map[i + 1])
	{
		if (!ft_is_charset(map[i], VALID_OBJECT) ||
			!ft_is_charset(map[i + 1], VALID_OBJECT))
			return (set_err_msg(INVALID_CHAR, data), 1);
		if (map[i] == '\n' && map[i + 1] == '\n')
			return(set_err_msg(EMPTY_LINES, data), 1);
		i++;
	}
	return (0);
}

int	read_map(char *filename, t_data *data)
{
	int fd;
	char *line;
	char *map;
	int		err;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (set_err_msg(NO_MAP, data), 1);
	map = ft_calloc(1, sizeof(char));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map = ft_strjoin_n_free(map, line);
		free(line);
		if (!map)
			return (set_err_msg(MALLOC_ERROR_MSG, data), 1);
		data->map->row++;
		if (data->map->row > (data->max_row / TILE_SIZE))
		{
			free(map);
			return (set_err_msg(MAP_TOO_BIG, data), 1);
		}

	}
	ft_printf("map :\n%s\n", map);
	if (validate_map_content(map, data) == 1)
	{
		free(map);
		return (1);
	}
	close(fd);
	// parse the map using a static
	// matrix[row_max / TILESET][col_max / TILESET]
	// int or char?
	// then after all the parsing and checking the map
	// is solvable store it in a **martix which we know
	// for sure the size and and is valid

	free(map);
	return (0);
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


// to implement later to play fullscreen
// if (av[2] && (!ft_strncmp(av[2], "fullscreen", 11)))
// {
// 	mlx_get_screen_size(data.mlx, &(data.map->col), &(data.map->row));
// 	data.map->row /= TILE_SIZE;
// 	data.map->col /= TILE_SIZE;
// }