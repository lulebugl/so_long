/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:33:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/08 20:43:50 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "assets.h"

# define MALLOC_ERROR 1
# define FULLSCREEN 0

# define MAX_ROW 3840 / TILE_SIZE // 64
# define MAX_COL 2160 / TILE_SIZE // 33

typedef struct s_map
{
//	char	*map;
	char	**matrix;
	int		row;
	int		col;
}			t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*textures[5];
	int		max_row;
	int		max_col;
	t_map	*map;
}			t_data;

// parsing
int parse_arguments(int ac, char **av, t_data *data);

// Events.c
int on_keypress(int keysym, t_data *data);
int on_destroy(t_data *data);

// error.c
void 	display_err_and_exit(char const *msg, t_data *data);

# define MAP_TOO_BIG "Map too big for the screen resolution\n"
# define WRONG_EXTENSION "Map file extention is wrong (.ber expected).\n"
# define NO_MAP "The Map couldn't be opened. Does it exist?\n"
# define MALLOC_ERROR_MSG "Memory allocation failed.\n"
# define MALLOC_ERROR_MSG "Memory allocation failed.\n"
# define EMPTY_LINES "Your map has empty lines\n"

#endif