/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:49:54 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 14:31:53 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	close_and_free(void *str, int fd)
{
	close(fd);
	free(str);
}

void	print_matrix(int **matrix, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map->row)
	{
		j = -1;
		while (++j < data->map->col)
			ft_printf("%c", (char)matrix[i][j]);
		ft_printf("\n");
	}
}
