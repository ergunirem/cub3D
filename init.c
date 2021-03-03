/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 20:49:48 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/03/03 17:38:27 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_window *window)
{
	if (!(window->map = malloc(sizeof(t_map))))
		ft_exit("Malloc failed\n");
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
	if (!(window->textures = malloc(sizeof(t_tex))))
		ft_exit("Malloc failed\n");
	if (!(window->textures->north = malloc(sizeof(t_image *))))
		ft_exit("Malloc failed\n");
	if (!(window->textures->south = malloc(sizeof(t_image *))))
		ft_exit("Malloc failed\n");
	if (!(window->textures->west = malloc(sizeof(t_image *))))
		ft_exit("Malloc failed\n");
	if (!(window->textures->east = malloc(sizeof(t_image *))))
		ft_exit("Malloc failed\n");
	if (!(window->textures->sprite = malloc(sizeof(t_image *))))
		ft_exit("Malloc failed\n");
	window->textures->north->endian = -1;
	window->textures->south->endian = -1;
	window->textures->east->endian = -1;
	window->textures->west->endian = -1;
	window->textures->sprite->endian = -1;
}
