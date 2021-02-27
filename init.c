/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 20:49:48 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/02/27 07:52:52 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_window *window, t_map *map)
{
	window->map = map;
	window->map->map_started = FALSE;
	window->map->row_pos = 0;
	window->map->col_pos = 0;
	window->map->max_row = 0;
	window->map->max_col = 0;
	window->map->floor_color = -1;
	window->map->ceiling_color = -1;
}

void	init_textures(t_window *window, t_tex *textures)
{
	t_image		*north;
	t_image		*south;
	t_image		*east;
	t_image		*west;
	t_image		*sprite;

	window->textures = textures;
	window->textures->north = north;
	window->textures->south = south;
	window->textures->east = east;
	window->textures->west = west;
	window->textures->sprite = sprite;
	// window->textures->north->endian = -1;
	// window->textures->south->endian = -1;
	// window->textures->east->endian = -1;
	// window->textures->west->endian = -1;
	// window->textures->sprite->endian = -1;
}
