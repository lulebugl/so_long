/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:28:23 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/11 17:06:00 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int collectible_exists(char *map)
{
	while (*map)
		if (*map++ == COLLECTIBLE)
			return (1);
	return (0);
}

static int player_exists(char *map)
{
	bool exist;

	while (*map)
	{
		if (*map == PLAYER && exist == true)
			return (0);
		if (*map == PLAYER)
			exist = true;
		map++;
	}
	if (exist == true)
		return (1);
	return (0);
}

// Check mthere is enough collectible, no empty lines, a player...
int	validate_map_content(char *map, t_data *data)
{
	int	i;

	i = 0;
	if (ft_strlen(map) < 3)
		return (set_err_msg(EMPTY_LINES, data), -1);
	if (*map == '\n' || !(*map))
		return (set_err_msg(EMPTY_LINES, data), -1);
	if (!player_exists(map))
		return (set_err_msg(NO_PLAYER, data), -1);
	if (!collectible_exists(map))
		return (set_err_msg(NO_COLLECTIBLE, data), -1);
	while (map[i] && map[i + 1])
	{
		if (!ft_is_charset(map[i], VALID_OBJECT) ||
			!ft_is_charset(map[i + 1], VALID_OBJECT))
			return (set_err_msg(INVALID_CHAR, data), -1);
		if (map[i] == '\n' && map[i + 1] == '\n')
			return(set_err_msg(EMPTY_LINES, data), -1);
		i++;
	}
	return (0);
}

int	validate_map_size(char *map, t_data *data)
{
	char 	**tab;
	int		col;
	int i;

	i = -1;
	tab = ft_split(map, '\n');
	if (!tab)
		return (set_err_msg(MALLOC_ERROR, data), 1);
	col = ft_strlen(tab[0]);
	ft_printf("max_col : %d\n", data->max_col / TILE_SIZE);
	ft_printf("col : %d\n", col);
	if (col > data->max_col / TILE_SIZE)
	{
		free_tab(tab);
		return (set_err_msg(MAP_TOO_BIG, data), 1);

	}
	while (tab[++i])
		if (ft_strlen(tab[i]) != col)
		{
			free_tab(tab);
			return (set_err_msg(MAP_NOT_RECTANGLE, data), 1);
		}
	data->map->col = col;
	free_tab(tab);
	return (1);
}
