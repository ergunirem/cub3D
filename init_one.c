/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_one.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 20:49:48 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/24 18:53:42 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_window *new_window)
{
	new_window->mlx = mlx_init();
	if (!new_window->mlx)
		ft_exit("mlx_init failed\n", new_window);
	new_window->height = 0;
	new_window->width = 0;
	new_window->screenshot = 0;
}

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
	window->map->floor_color = -1;
	window->map->ceiling_color = -1;
}

void	init_textures(t_window *window)
{
	window->textures = malloc(sizeof(t_tex));
	if (!window->textures)
		ft_exit("Malloc failed\n", window);
	window->textures->north = malloc(sizeof(t_image *));
	if (!window->textures->north)
		ft_exit("Malloc failed\n", window);
	window->textures->south = malloc(sizeof(t_image *));
	if (!window->textures->south)
		ft_exit("Malloc failed\n", window);
	window->textures->west = malloc(sizeof(t_image *));
	if (!window->textures->west)
		ft_exit("Malloc failed\n", window);
	window->textures->east = malloc(sizeof(t_image *));
	if (!window->textures->east)
		ft_exit("Malloc failed\n", window);
	window->textures->sprite = malloc(sizeof(t_image *));
	if (!window->textures->sprite)
		ft_exit("Malloc failed\n", window);
	window->textures->north->endian = -1;
	window->textures->south->endian = -1;
	window->textures->east->endian = -1;
	window->textures->west->endian = -1;
	window->textures->sprite->endian = -1;
}

void	init_player(t_window *window)
{
	window->player = malloc(sizeof(t_player));
	if (!window->player)
		ft_exit("Malloc failed\n", window);
	ft_bzero(window->player, sizeof(t_player));
	window->player->pos_x = -20.0;
	window->player->pos_y = -20.0;
	window->player->move_speed = 0.10;
	window->player->dir_x = 1.0;
	window->player->dir_y = 0.0;
	window->player->plane_x = -20.0;
	window->player->plane_y = -20.0;
	window->player->rotate_speed = 0.10;
	window->player->cam_height = 1.0;
	window->player->health = 20;
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
