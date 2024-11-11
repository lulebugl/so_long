/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:42:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/11 20:42:20 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	store_map(int fd, t_data *data, char **map)
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

static int	fill_matrix_row(int *row, char *tab_row)
{
	int	j;

	j = 0;
	while (tab_row[j])
	{
		if (tab_row[j] == 'P')
			row[j] = PLAYER;
		else if (tab_row[j] == 'C')
			row[j] = COLLECTIBLE;
		else if (tab_row[j] == '1')
			row[j] = OBSTACLE;
		else
			row[j] = 0;
		j++;
	}
	return (0);
}

int	create_matrix(char *map, char **tab, t_data *data)
{
	int	i;
	int	**matrix;

	i = -1;
	matrix = (int **)malloc(sizeof(int *) * data->map->row);
	if (!matrix)
		return (set_err_msg(MALLOC_ERROR, data), -1);
	while (++i < data->map->row)
	{
		matrix[i] = malloc(sizeof(int) * ft_strlen(tab[i]));
		if (!matrix[i])
		{
			free_matrix(matrix, i);
			free_tab(tab);
			return (set_err_msg(MALLOC_ERROR, data), -1);
		}
		fill_matrix_row(matrix[i], tab[i]);
	}
	data->map->matrix = matrix;
	// print_matrix(data->map->matrix, data);
	free(map);
	free_tab(tab);
	return (0);
}

static int	validate_fd_and_init(int fd, t_data *data, char **map)
{
	if (fd < 0 || !data || !map)
		display_err_and_exit(NO_MAP, data);
	*map = ft_calloc(1, sizeof(char));
	if (!*map)
		return (set_err_msg(MALLOC_ERROR, data), -1);
	return (0);
}

int	read_map(char *filename, t_data *data)
{
	int		fd;
	char	*map;
	char	**tab;

	fd = open(filename, O_RDONLY);
	if (validate_fd_and_init(fd, data, &map) != 0)
		return (-1);
	map = ft_calloc(1, sizeof(char));
	if (store_map(fd, data, &map) != 0)
		return (close_and_free(map, fd), -1);
	assert(map != NULL);
	// ft_printf("map :\n%s\n", map);
	if (validate_map_content(map, data) != 0)
		return (close_and_free(map, fd), -1);
	tab = validate_map_size(map, data);
	if (tab == NULL)
		return (close_and_free(map, fd), -1);
	if (create_matrix(map, tab, data) != 0)
		return (close_and_free(map, fd), -1);
	close(fd);
	return (0);
}
