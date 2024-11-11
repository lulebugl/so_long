/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:33:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/11 17:04:07 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "assets.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <assert.h>
# include <stdbool.h>
# include <fcntl.h>

# define FULLSCREEN 0

# define VALID_OBJECT "01CEP\n"
# define MAP_TOO_BIG "Map too big for the screen resolution.\n"
# define WRONG_EXTENSION "Map file extention is wrong (.ber expected).\n"
# define NO_MAP "The Map couldn't be opened. Does it exist?\n"
# define MALLOC_ERROR "Memory allocation failed.\n"
# define EMPTY_LINES "The map has empty lines.\n"
# define INVALID_CHAR "The map has an invalid element.\n"
# define MAP_NOT_RECTANGLE "The map has is not rectangle.\n"
# define NO_PLAYER "There is no or multiple players on the map.\n"
# define NO_COLLECTIBLE "There is no collectibles on the map.\n"

# define PLAYER	'P'
# define COLLECTIBLE 'C'

typedef struct s_map
{
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
	char	*err_msg;
	t_map	*map;
}			t_data;

// parsing
int			parse_arguments(int ac, char **av, t_data *data);
int			read_map(char *filename, t_data *data);
int			validate_map_content(char *map, t_data *data);
int			validate_map_size(char *map, t_data *data);


// Events.c
int			on_keypress(int keysym, t_data *data);
int			on_destroy(t_data *data);

// error.c
void		display_err_and_exit(const char *msg, t_data *data);
void		set_err_msg(char *msg, t_data *data);

// utils.c
void		free_tab(char **tab);
void 		free_matrix(int **matrix, int i);


#endif