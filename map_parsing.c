/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:42:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/08 21:20:51 by llebugle         ###   ########.fr       */
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
char	*ft_strjoin_n(char *s1, char const *s2)
{
	char	*new;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);

	i = -1;
	while (s1[++i] && i < len)
		new[i] = s1[i];
	j = -1;
	while (s2[++j] && i + j < len)
		new[i + j] = s2[j];
	new[i + j] = '\0';
	free(s1);
	return (new);
}

int	is_map_full(char *map)
{
	int	i;
	int len_map;

	i = 0;
	len_map = ft_strlen(map);
	if (len_map < 3)
		return (-1);
	if (*map == '\n' || !(*map))
		return (-1);
	while (map[i] && map[i + 1])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
			return (-1);
		i++;
	}
	return (0);
}

void	read_map(char *filename, t_data *data)
{
	int fd;
	char *line;
	char *map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		display_err_and_exit(NO_MAP, data);
	map = ft_calloc(1, sizeof(char));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map = ft_strjoin_n(map, line);
		free(line);
		if (!map)
			display_err_and_exit(MALLOC_ERROR_MSG, data);
		data->map->row++;
		if (data->map->row > (data->max_row / TILE_SIZE))
		{
			free(map);
			display_err_and_exit(MAP_TOO_BIG, data);
		}
	}
	ft_printf("map :\n%s\n", map);
	if (is_map_full(map) == -1)
	{
		free(map);
		display_err_and_exit(EMPTY_LINES, data);
	}
	close(fd);

	// parse the map using a static
	// matrix[row_max / TILESET][col_max / TILESET]
	// int or char?
	// then after all the parsing and checking the map
	// is solvable store it in a **martix which we know
	// for sure the size and and is valid

	free(map);
}

int parse_arguments(int ac, char **av, t_data *data)
{
	check_arguments(ac, av, data);
	mlx_get_screen_size(data->mlx, &(data->max_col), &(data->max_row));
	ft_printf("max_row : %d\n", data->max_row);
	ft_printf("max_col : %d\n", data->max_col);
	read_map(av[1], data);
	return (0);
}


// to implement later to play fullscreen
// if (av[2] && (!ft_strncmp(av[2], "fullscreen", 11)))
// {
// 	mlx_get_screen_size(data.mlx, &(data.map->col), &(data.map->row));
// 	data.map->row /= TILE_SIZE;
// 	data.map->col /= TILE_SIZE;
// }