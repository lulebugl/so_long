/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:33:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/15 16:29:38 by llebugle         ###   ########.fr       */
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
# include <fcntl.h>
# include <stdbool.h>

# define FULLSCREEN 0

# define VALID_OBJECT "01CEP\n"
# define MAP_TOO_BIG "Map too big for the screen resolution.\n"
# define WRONG_EXTENSION "Map file extention is wrong (.ber expected).\n"
# define NO_MAP "The Map couldn't be opened. Does it exist?\n"
# define MALLOC_ERROR "Memory allocation failed.\n"
# define EMPTY_LINES "The map has empty lines.\n"
# define INVALID_CHAR "The map has an invalid element.\n"
# define MAP_NOT_RECTANGLE "The map has is not rectangle.\n"
# define NO_PLAYER_OR_EXIT "Invalid number of exit or players on the map.\n"
# define NO_COLLECTIBLE "There is no collectibles on the map.\n"
# define INVALID_PATH "Some collectibles can't be reached.\n"
# define INVALID_EXIT "Exit can't be reached.\n"
# define MAP_NOT_CLOSED "The map is not closed.\n"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0;37m"

# define TILE_SIZE 64

typedef enum e_map_element
{
	EMPTY = (int)'0',
	WALL = (int)'1',
	COLLECTIBLE = (int)'C',
	PLAYER = (int)'P',
	EXIT = (int)'E',
	WATER = (int)'W',
	TREE = (int)'T',
}			t_map_element;

typedef struct s_position
{
	int		x;
	int		y;
}			t_pos;

typedef enum e_tile_type {
 //   GRASS_SINGLE = 0,
    GRASS_TOP = 1,
    GRASS_RIGHT = 2,
    GRASS_BOTTOM = 3,
    GRASS_LEFT = 4,
    GRASS_TOP_RIGHT = 5,
    GRASS_BOTTOM_RIGHT = 6,
    GRASS_BOTTOM_LEFT = 7,
    GRASS_TOP_LEFT = 8,
    // GRASS_HORIZONTAL = 9,
    // GRASS_VERTICAL = 10,
    GRASS_ALL = 11
} t_tile_type;

typedef struct s_textures
{
    void    *empty[12];
    void    *empty_tcl;
    void    *obstacle;
    void    *collectible;
    void    *player;
    void    *exit;
    void    *water;
}   t_textures;

typedef struct s_map
{
	int		**matrix;
	int		row;
	int		col;
	int		nb_collectible;
	t_pos	player;
	t_pos	exit;
}			t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_textures	textures;
	int		max_row;
	int		max_col;
	char	*err_msg;
	t_map	*map;
}			t_data;

// parsing
int			parse_arguments(int ac, char **av, t_data *data);

// Events.c
int			on_keypress(int keysym, t_data *data);
int			on_destroy(t_data *data);

// error.c
void		display_err_and_exit(const char *msg, t_data *data);
void		set_err_msg(char *msg, t_data *data);


// map
int			read_map(char *filename, t_data *data);
int			validate_map_content(char *map, t_data *data);
char		**validate_map_size(char *map, t_data *data);
int			is_map_solvable(t_data *data);

int			create_matrix(char *map, char **tab, t_data *data);

// game.c
void	launch_game(t_data *data);


// render
void    load_textures(t_data *data);
void    *get_texture_for_element(t_data *data, int element, int x, int y);



// utils.c
void		free_matrix(int **matrix, int i);
void		close_and_free(void *str, int fd);
void		print_matrix(int **matrix, t_data *data);
void		debug_print(t_data *data, char *location);
int		 	is_obstacle(t_map_element element);

#endif