/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:42:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/11 17:06:48 by llebugle         ###   ########.fr       */
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

int	create_matrix(char *map, t_data *data)
{
	char	*tmp;
	int		i;
	int		j;
	int		**matrix;

	i = -1;
	j = 0;
	tmp = map;
	matrix = (int **)malloc(sizeof(int *) * data->map->row);
	if (!matrix)
		return (set_err_msg(MALLOC_ERROR, data), -1);
	while (++i < data->map->row)
	{
		matrix[i] = (int *)malloc(sizeof(int) * data->map->col);
		if (!matrix[i])
		{
			free_matrix(matrix, i);
			return (set_err_msg(MALLOC_ERROR, data), -1);
		}
		while (*tmp && *tmp != '\n')
		// if (*tmp == '\n')
		// {
			
		// 	i++;
		// }
		else
			matrix[i][j++] = tmp;
		tmp++;
	}
	free(map);
	printf("test\n");
	i = -1;
	int row = data->map->row;
	int col = data->map->col;
	while (++i < row)
	{
		j = -1;
		while (++j < col)
			printf("%d\n", matrix[i][j]);
	}
	return (0);
}
int	read_map(char *filename, t_data *data)
{
	int		fd;
	char	*map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (set_err_msg(NO_MAP, data), -1);
	map = ft_calloc(1, sizeof(char));
	if (store_map(fd, data, &map) != 0)
		return (free(map), -1);
	assert(map != NULL);
	ft_printf("map :\n%s\n", map);
	if (validate_map_content(map, data) != 0)
		return (free(map), -1);
	if (validate_map_size(map, data) != 0)
		return (free(map), -1);
	if (create_matrix(map, data))
		return (free(map), -1);
	close(fd);
	free(map);
	return (0);
}
