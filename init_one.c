/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_one.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 20:49:48 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/28 16:26:32 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_window *window)
{
	window->map = malloc(sizeof(t_map));
	if (!window->map)
		ft_exit("Malloc failed\n", window);
	window->map->map_started = FALSE;
	window->map->row_pos = 0;
	window->map->col_pos = 0;
	window->map->max_row = 0;
	window->map->max_col = 0;
	window->map->arr_malloc = 0;
	window->map->floor_color = -1;
	window->map->ceiling_color = -1;
}

t_tex	init_textures(t_window *window)
{
	t_tex	textures;

	textures.tex_num = 0;
	textures.tex_x = 0;
	textures.tex_y = 0;
	textures.width = 0;
	textures.height = 0;
	textures.wall_x = 0;
	textures.tex_pos = 0;
	textures.step = 0;
	return (textures);
}

t_player	init_player(t_window *window)
{
	t_player	player;

	player.pos_x = -20.0;
	player.pos_y = -20.0;
	player.move_speed = 0.10;
	player.dir_x = 1.0;
	player.dir_y = 0.0;
	player.plane_x = -20.0;
	player.plane_y = -20.0;
	player.rotate_speed = 0.10;
	player.cam_height = 1.0;
	player.health = 20;
	return (player);
}

void	init_keys(t_window *window)
{
	window->keys = malloc(sizeof(t_keys));
	if (!window->keys)
		ft_exit("Malloc failed\n", window);
	ft_bzero(window->keys, sizeof(t_keys));
	window->keys->forward = 0;
	window->keys->backward = 0;
	window->keys->left = 0;
	window->keys->right = 0;
	window->keys->look_left = 0;
	window->keys->look_right = 0;
	window->keys->close = 0;
}

void	init_image(t_window *window)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	if (!image)
		ft_exit("Malloc failed\n", window);
	ft_bzero(image, sizeof(t_image));
	image->img = mlx_new_image(window->mlx, window->width, window->height);
	window->image_malloc = 1;
	if (!image->img)
		ft_exit("mlx_new_image failed\n", window);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	image->width = window->width;
	image->height = window->height;
	window->image = image;
}
