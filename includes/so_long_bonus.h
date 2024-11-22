/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:33:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/22 21:56:02 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "assets.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <assert.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <time.h>

/* Constants */
# define TILE_SIZE 64
# define TRANSPARENCY_COLOR 0xFF000000
# define VALID_OBJECT "01CEP\n"
# define ENNEMY -1
# define DROWNED -2
# define SHEEP_FRAMES 6

/* Colors */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0;37m"

/* Error Messages */
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
	TEX_TOP_TREE,
	TEX_TRUNK,
	TEX_COLLECTIBLE,
	TEX_PLAYER,
	TEX_BANNER,
	TEX_EXIT,
	TEX_WATER,
	TEX_BUSH,
	TEX_FOAM,
	TEX_GOBLIN,
	TEX_COUNT,
}				t_texture_type;

typedef struct s_position
{
	int			x;
	int			y;
}				t_pos;

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

typedef struct s_animation
{
	t_texture	*frames[SHEEP_FRAMES];
	int			current_frame;
	int			frame_count;
	int			frame_delay;
	int			delay_counter;
}				t_animation;

typedef struct s_keys
{
	int			left;
	int			right;
	int			up;
	int			down;
}				t_keys;

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
	t_img		img;
	t_texture	*textures[TEX_COUNT];
	int			max_row;
	int			max_col;
	char		*err_msg;
	int			nb_moves;
	t_animation	sheep;
	bool		pause;
	bool		end;
	t_map		*map;
}				t_data;

typedef enum e_map_element
{
	EMPTY = '0',
	OBSTACLE = '1',
	COLLECTIBLE = 'C',
	PLAYER = 'P',
	EXIT = 'E',
	WATER = 'W',
	TREE = '1',
	TRUNK = '[',
	BUSH = '&',
	BANNER = 'B',
	GOBLIN = 'G',
	FOAM = '$',
}				t_map_element;

typedef struct s_check
{
	bool		reached_exit;
	int			collectibles;
}				t_check;

typedef struct s_pathfind
{
	t_pos		*queue;
	int			**visited;
	int			*front;
	int			*rear;
	t_check		*check;
}				t_pathfind;

/* parsing */
int				parse_arguments(int ac, char **av, t_data *data);

/* move_player.c */
void			move_player(const char *direction, t_data *data);
void			update_player_position(t_data *data, t_pos next);

/* animation.c */
void			init_sheep_animation(t_data *data);
void			update_sheep_animation(t_data *data);

/* bfs.c */
bool			check_paths_bfs(t_data *data, t_pathfind *pf);

/*
** spawn_tnt.c
** spawn_tnt_utils.c
*/
double			get_spawn_rate(t_data *data);
int				collect_empty_spots(t_data *data, int *empty_spots);
void			cleanup_pathfinding(int **visited, t_pos *queue, int row);
void			spawn_tnt(t_data *data);

/* game.c */
void			init_window(t_data *data);
void			erase_player_last_pos(t_pos player, t_data *data);
int				update_map(t_data *data);
void			launch_game(t_data *data);

/* events.c */
int				on_keypress(int keysym, t_data *data);
int				on_keyrelease(int keysym, t_data *data);

/* events_utils.c */
void			ft_lost(t_data *data, t_pos next);
void			ft_drowned(t_data *data, t_pos next);
int				on_destroy(t_data *data);
char			*get_direction(int keysym);
void			ft_victory(t_data *data);

/* map_init.c */
int				read_map(char *filename, t_data *data);

/* map_validation.c */
int				validate_map_content(char *map, t_data *data);
char			**validate_map_size(char *map, t_data *data);

/* map_solver.c */
int				**create_visited_matrix(t_data *data);
int				is_map_solvable(t_data *data);

/* matrix.c */
int				create_matrix(char *map, char **tab, t_data *data);
void			free_matrix(int **matrix, int i);

/* update_matrix.c */
int				update_matrix(t_data *data);

/* render.c */
void			render_banner(t_data *data);
void			render_grass(t_data *data);
void			render_water(t_data *data);
void			render_foam(t_data *data);
int				render_obstacles(t_data *data);

/* textures.c */
t_texture		*load_texture(void *mlx, char *path);
void			load_textures(t_data *data);
t_texture		*get_texture_for_elem(t_data *data, int element, int x, int y);

/* draw.c */
void			draw_texture(t_img *img, t_texture *tex, int start_x,
					int start_y);
void			draw_top_tree(t_pos player, t_data *data);

/* autotiling.c */
t_texture_type	check_adjacent(t_data *data, int x, int y);
void			get_adjacent_tiles(t_data *data, int x, int y, int *adjacent);

/* error.c */
void			clean_up(t_data *data);
void			display_err_and_exit(const char *msg, t_data *data);
void			set_err_msg(char *msg, t_data *data);

/* map_utils */
void			close_and_free(void *str, int fd);
void			print_matrix(int **matrix, t_data *data);

/* utils.c */
int				is_obstacle(t_map_element element);
void			debug_print(t_data *data, char *location);
void			free_matrix(int **matrix, int i);

#endif