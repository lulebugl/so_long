/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:48:23 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 14:31:53 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	check_arguments(int ac, char **av, t_data *data)
{
	int	len;

	if (ac < 2)
		display_err_and_exit("The map is missing.\n", data);
	len = ft_strlen(av[1]);
	if (!ft_strnstr(&av[1][len - 4], ".ber", 4))
		display_err_and_exit(WRONG_EXTENSION, data);
}

int	parse_arguments(int ac, char **av, t_data *data)
{
	check_arguments(ac, av, data);
	mlx_get_screen_size(data->mlx, &(data->max_col), &(data->max_row));
	if (read_map(av[1], data) != 0)
		display_err_and_exit(NULL, data);
	return (0);
}
