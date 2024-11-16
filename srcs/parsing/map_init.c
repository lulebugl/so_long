/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:40:43 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/15 15:00:40 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	validate_fd_and_init(int fd, t_data *data, char **map)
{
	if (fd < 0 || !data || !map)
		display_err_and_exit(NO_MAP, data);
	*map = ft_calloc(1, sizeof(char));
	if (!*map)
		return (set_err_msg(MALLOC_ERROR, data), -1);
	return (0);
}

static int	store_map(int fd, t_data *data, char **map)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		*map = ft_strjoin_n_free(*map, line);
		free(line);
		if (!*map)
			return (set_err_msg(MALLOC_ERROR, data), -1);
		data->map->row++;
		if (data->map->row > (data->max_row / TILE_SIZE))
			return (set_err_msg(MAP_TOO_BIG, data), -1);
	}
	return (0);
}

int	map_closed_by_obstacle(char **tab, t_data *data)
{
	int	i;

	i = 0;
	while (tab[0][i])
	{
		if (!is_obstacle(tab[0][i]))
			return (data->err_msg = MAP_NOT_CLOSED, 0);
		tab[0][i++] = WATER;
	}
	i = 0;
	while (++i < data->map->row - 1)
	{
		if (!is_obstacle(tab[i][0]) ||
			!is_obstacle(tab[i][data->map->col- 1]))
			return (data->err_msg = MAP_NOT_CLOSED, 0);
		tab[i][0] = WATER;
		tab[i][data->map->col - 1] = WATER;
	}
	i = 0;
	while (tab[data->map->row - 1][i])
	{
		if (!is_obstacle(tab[data->map->row - 1][i]))
			return (data->err_msg = MAP_NOT_CLOSED, 0);
		tab[data->map->row - 1][i++] = WATER;
	}
	return (1);
}

int	read_map(char *filename, t_data *data)
{
	int		fd;
	char	*map;
	char	**tab;

	fd = open(filename, O_RDONLY);
	if (validate_fd_and_init(fd, data, &map) != 0)
		return (-1);
	if (store_map(fd, data, &map) != 0)
		return (close_and_free(map, fd), -1);
	assert(map != NULL);
	if (validate_map_content(map, data) != 0)
		return (close_and_free(map, fd), -1);
	tab = validate_map_size(map, data);
	if (tab == NULL)
		return (close_and_free(map, fd), -1);
	if (!map_closed_by_obstacle(tab, data))
	{
		ft_free_tab(tab);
		return (close_and_free(map, fd), -1);
	}
	if (create_matrix(map, tab, data) != 0)
		return (close_and_free(map, fd), -1);
	close(fd);
	return (0);
}
