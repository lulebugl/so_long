/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:00:14 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/15 21:23:40 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_texture *load_texture(void *mlx, char *path)
{
    t_texture *tex;
    int     tmp;

    tex = malloc(sizeof(t_texture));
    if (!tex)
        return (NULL);
    tex->img.img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
    if (!tex->img.img)
    {
        free(tex);
        return (NULL);
    }
	printf("test\n");
    tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bits_per_pixel,
        &tex->img.line_length, &tex->img.endian);
    tex->data = (int *)malloc(sizeof(int) * (tex->width * tex->height));
    if (!tex->data)
    {
        mlx_destroy_image(mlx, tex->img.img);
        free(tex);
        return (NULL);
    }
    // Copy pixel data
    tmp = -1;
    while (++tmp < tex->width * tex->height)
        tex->data[tmp] = ((int *)tex->img.addr)[tmp];
    mlx_destroy_image(mlx, tex->img.img);
    return (tex);
}

void    draw_pixel(t_img *img, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || y < 0)
        return;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    draw_texture(t_img *img, t_texture *tex, int start_x, int start_y)
{
    int x;
    int y;
    int color;

    y = -1;
	printf("%d\n", tex->height);
	printf("%d\n", tex->width);
	printf("%d\n", tex->img.height);
	printf("%d\n", tex->img.width);
    while (++y < tex->height)
    {
        x = -1;
        while (++x < tex->width)
        {
            color = tex->data[y * tex->width + x];
            if (color != (int)0xFF000000 ) // Skip transparent pixels
                draw_pixel(img, start_x + x, start_y + y, color);
        }
    }
}

void load_textures(t_data *data)
{
    // Initialize all texture pointers to NULL
	debug_print(data, 0);
    ft_memset(data->textures, 0, sizeof(data->textures));
    
    // Load grass variants
    data->textures[TEX_GRASS_ALL] = load_texture(data->mlx, GRASS);
    data->textures[TEX_GRASS_TOP] = load_texture(data->mlx, GRASS_TM);
    data->textures[TEX_GRASS_RIGHT] = load_texture(data->mlx, GRASS_MR);
    data->textures[TEX_GRASS_BOTTOM] = load_texture(data->mlx, GRASS_BM);
    data->textures[TEX_GRASS_LEFT] = load_texture(data->mlx, GRASS_ML);

    data->textures[TEX_GRASS_TOP_RIGHT] = load_texture(data->mlx, GRASS_TCR);
    data->textures[TEX_GRASS_BOTTOM_RIGHT] = load_texture(data->mlx, GRASS_BCR);
    data->textures[TEX_GRASS_BOTTOM_LEFT] = load_texture(data->mlx, GRASS_BCL);
    data->textures[TEX_GRASS_TOP_LEFT] = load_texture(data->mlx, GRASS_TCL);
    
    // Load other textures
    data->textures[TEX_OBSTACLE] = load_texture(data->mlx, OBSTACLE_PATH);
    data->textures[TEX_WATER] = load_texture(data->mlx, WATER_PATH);
    data->textures[TEX_COLLECTIBLE] = load_texture(data->mlx, GRASS);
    data->textures[TEX_PLAYER] = load_texture(data->mlx, PLAYER_PATH);
    data->textures[TEX_EXIT] = load_texture(data->mlx, GRASS);
	debug_print(data,0);

	printf("test8\n");
    // Verify all textures loaded successfully
    for (int i = 0; i < TEX_COUNT; i++) {
        if (!data->textures[i]) {
            display_err_and_exit("Failed to load textures", data);
        }
    }
	printf("test10\n");

}

static t_texture_type check_adjacent(t_data *data, int x, int y)
{
    int top = 1;
    int right = 1;
    int bottom = 1;
    int left = 1;

    if (x > 0)
        top = !is_obstacle(data->map->matrix[x - 1][y]);
    if (y < data->map->col - 1)
        right = !is_obstacle(data->map->matrix[x][y + 1]);
    if (x < data->map->row - 1)
        bottom = !is_obstacle(data->map->matrix[x + 1][y]);
    if (y > 0)
        left = !is_obstacle(data->map->matrix[x][y - 1]);

    // Return appropriate texture type based on surroundings
    if (!top && !right && !bottom && !left)
        return TEX_GRASS_ALL;
    if (!top && !bottom && !left && right)
        return TEX_GRASS_RIGHT;
    if (!top && !bottom && left && !right)
        return TEX_GRASS_LEFT;
    if (!top && bottom && !left && !right)
        return TEX_GRASS_BOTTOM;
    if (top && !bottom && !left && !right)
        return TEX_GRASS_TOP;
    if (!top && !right && bottom && left)
        return TEX_GRASS_BOTTOM_LEFT;
    if (!top && right && bottom && !left)
        return TEX_GRASS_BOTTOM_RIGHT;
    if (top && !right && !bottom && left)
        return TEX_GRASS_TOP_LEFT;
    if (top && right && !bottom && !left)
        return TEX_GRASS_TOP_RIGHT;
    
    // Default cases
    if (!top && !bottom && left && right)
        return TEX_GRASS_ALL;
    if (top && !right && bottom && !left)
        return TEX_GRASS_ALL;
        
    return TEX_GRASS_ALL;
}

t_texture *get_texture_for_element(t_data *data, int element, int x, int y)
{
    if (element == EMPTY)
    {
        t_texture_type tex_type = check_adjacent(data, x, y);
        return data->textures[tex_type];
    }
    if (element == WALL)
        return data->textures[TEX_WATER];
    if (element == COLLECTIBLE)
        return data->textures[TEX_COLLECTIBLE];
    if (element == PLAYER)
        return data->textures[TEX_PLAYER];
    if (element == EXIT)
        return data->textures[TEX_EXIT];
    if (element == WATER)
        return data->textures[TEX_WATER];

    return data->textures[TEX_GRASS_ALL]; // Default fallback
}

// Don't forget to add cleanup
void cleanup_textures(t_data *data)
{
    for (int i = 0; i < TEX_COUNT; i++) {
        if (data->textures[i]) {
            if (data->textures[i]->data)
                free(data->textures[i]->data);
            free(data->textures[i]);
            data->textures[i] = NULL;
        }
    }
}