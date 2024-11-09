/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:42:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/09 18:53:42 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int store_map(int fd, t_data *data, char **map)
{
	char *line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		*map = ft_strjoin_n_free(*map, line);
		free(line);
		if (!*map)
			return (set_err_msg(MALLOC_ERROR, data), 1);
		data->map->row++;
		if (data->map->row > (data->max_row / TILE_SIZE))
		{
			free(map);
			return (set_err_msg(MAP_TOO_BIG, data), 1);
		}
	}
	return (0);
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

void	check_map_lenght(char *map, t_data *data)
{
	char **tab;

	tab = ft_split(map, '\n');
	if (!tab)
	{
		free(map);
		display_err_and_exit(MALLOC_ERROR, data);
	}
	while (tab)
	{
		printf("%s", *tab);
		tab++;
	}
}

int	read_map(char *filename, t_data *data)
{
	int		fd;
	char	*map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (set_err_msg(NO_MAP, data), 1);
	map = ft_calloc(1, sizeof(char));
	if (store_map(fd, data, &map) != 0)
		return (1);
	assert(map != NULL);
	ft_printf("map :\n%s\n", map);
	if (validate_map_content(map, data) == 1)
		return (free(map), 1);
	check_map_lenght(map, data);
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
