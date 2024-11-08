/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:33:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/08 13:22:07 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

# include <stdio.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define GRASS "./assets/green_grass.xpm"
# define NINJA "./assets/ninja.xpm"

#define TILE_SIZE 64

typedef struct s_map
{
	int		row;
	int		col;
}			t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*textures[5];
	t_map	*map;
}			t_data;


// Events.c
int on_keypress(int keysym, t_data *data);
int on_destroy(t_data *data);

#endif