/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:33:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/18 18:59:52 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
// # include "../minilibx-linux/mlx_int.h"
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

# define TRANSPARENCY_COLOR 0xFF000000

# define TILE_SIZE 64

typedef enum e_map_element
{
	EMPTY = (int)'0',
	OBSTACLE = (int)'1',
	COLLECTIBLE = (int)'C',
	PLAYER = (int)'P',
	EXIT = (int)'E',
	WATER = (int)'W',
	TREE = (int)'1',
	TRUNK = (int)'[',
	BANNER = (int)'B',
}				t_map_element;

typedef struct s_position
{
	int			x;
	int			y;
}				t_pos;

typedef enum e_texture_type
{
	TEX_GRASS_ALL,
	TEX_GRASS_TOP,
	TEX_GRASS_RIGHT,
	TEX_GRASS_BOTTOM,
	TEX_GRASS_LEFT,
	TEX_GRASS_TOP_RIGHT,
	TEX_GRASS_BOTTOM_RIGHT,
	TEX_GRASS_BOTTOM_LEFT,
	TEX_GRASS_TOP_LEFT,
	TEX_GRASS_HR,
	TEX_GRASS_HL,
	TEX_GRASS_HM,
	TEX_GRASS_VT,
	TEX_GRASS_VB,
	TEX_GRASS_VM,
	TEX_GRASS_SINGLE,
	TEX_TREE,
	TEX_TRUNK,
	TEX_COLLECTIBLE,
	TEX_PLAYER,
	TEX_BANNER,
	TEX_EXIT,
	TEX_WATER,
	TEX_COUNT,
}				t_texture_type;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_texture
{
	t_img		img;
	int			*data;
	int			width;
	int			height;
	int			offset_x;
	int			offset_y;
}				t_texture;

typedef struct s_map
{
	int			**matrix;
	int			row;
	int			col;
	int			nb_collectible;
	t_pos		player;
	t_pos		player_prev;
	t_pos		exit;
}				t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img 		img;
	t_texture	*textures[TEX_COUNT];
	int			max_row;
	int			max_col;
	char		*err_msg;
	int			nb_moves;
	t_map		*map;
}				t_data;

// parsing
int				parse_arguments(int ac, char **av, t_data *data);

// Events.c
int				on_keypress(int keysym, t_data *data);
int				on_destroy(t_data *data);

// error.c
void			display_err_and_exit(const char *msg, t_data *data);
void			set_err_msg(char *msg, t_data *data);

// map
int				read_map(char *filename, t_data *data);
int				validate_map_content(char *map, t_data *data);
char			**validate_map_size(char *map, t_data *data);
int				is_map_solvable(t_data *data);

int				create_matrix(char *map, char **tab, t_data *data);

// game.c
void			launch_game(t_data *data);

// render
void			load_textures(t_data *data);
t_texture		*get_texture_for_elem(t_data *data, int element, int x,
					int y);
void			draw_texture(t_img *img, t_texture *tex, int start_x,
					int start_y);

// utils.c
t_texture_type	check_adjacent(t_data *data, int x, int y);
void			free_matrix(int **matrix, int i);
void			close_and_free(void *str, int fd);
void			print_matrix(int **matrix, t_data *data);
void			debug_print(t_data *data, char *location);
void			print_player_pos(t_pos player);

int				is_obstacle(t_map_element element);

void			clean_up(t_data *data);

void			render_grass(t_data *data);
void			render_water(t_data *data);
int				render_map(t_data *data);
void			move_player(const char *direction, t_data *data);


#endif