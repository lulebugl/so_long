/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:28:23 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 14:31:53 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

static int	collectible_exists(char *map)
{
	while (map && *map)
		if (*map++ == 'C')
			return (1);
	return (0);
}

static int	player_or_map_exists(char *map)
{
	bool	player;
	bool	exit;

	player = false;
	exit = false;
	while (map && *map)
	{
		if (*map == 'E' && exit == true)
			return (0);
		if (*map == 'P' && player == true)
			return (0);
		if (*map == 'P')
			player = true;
		if (*map == 'E')
			exit = true;
		map++;
	}
	if (exit == true && player == true)
		return (1);
	return (0);
}

// Check there is enough collectible, no empty lines, a player...
int	validate_map_content(char *map, t_data *data)
{
	int	i;

	i = 0;
	if (ft_strlen(map) < 3)
		return (set_err_msg(EMPTY_LINES, data), -1);
	if (*map == '\n' || !(*map))
		return (set_err_msg(EMPTY_LINES, data), -1);
	if (!player_or_map_exists(map))
		return (set_err_msg(NO_PLAYER_OR_EXIT, data), -1);
	if (!collectible_exists(map))
		return (set_err_msg(NO_COLLECTIBLE, data), -1);
	while (map[i] && map[i + 1])
	{
		if (!ft_is_charset(map[i], VALID_OBJECT) || !ft_is_charset(map[i + 1],
				VALID_OBJECT))
			return (set_err_msg(INVALID_CHAR, data), -1);
		if (map[i] == '\n' && map[i + 1] == '\n')
			return (set_err_msg(EMPTY_LINES, data), -1);
		i++;
	}
	return (0);
}

char	**validate_map_size(char *map, t_data *data)
{
	char	**tab;
	int		col;
	int		i;

	i = -1;
	tab = ft_split(map, '\n');
	if (!tab)
		return (set_err_msg(MALLOC_ERROR, data), NULL);
	col = ft_strlen(tab[0]);
	if (col > data->max_col / TILE_SIZE)
	{
		ft_free_tab(tab);
		return (set_err_msg(MAP_TOO_BIG, data), NULL);
	}
	while (tab[++i])
	{
		if ((int)ft_strlen(tab[i]) != col)
		{
			ft_free_tab(tab);
			return (set_err_msg(MAP_NOT_RECTANGLE, data), NULL);
		}
	}
	data->map->col = col;
	return (tab);
}
