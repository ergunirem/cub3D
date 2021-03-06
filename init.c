/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 20:49:48 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/03/06 23:12:09 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_window	*init_window(void)
{
	t_window *new_window;

	new_window = (t_window*)malloc(sizeof(t_window));
	if (!new_window)
		ft_exit("init malloc failed\n");
	ft_bzero(new_window, sizeof(t_window));
	new_window->mlx = mlx_init();
	if (!new_window->mlx)
		ft_exit("mlx_init failed\n");
	new_window->height = 0;
	new_window->width = 0;
	new_window->screenshot = 0;
	return (new_window);

}

void	init_map(t_window *window)
{
	t_image *image;
	if (!(window->map = malloc(sizeof(t_map))))
		ft_exit("Malloc failed\n");
	window->map->map_started = FALSE;
	window->map->row_pos = 0;
	window->map->col_pos = 0;
	window->map->max_row = 0;
	window->map->max_col = 0;
	window->map->floor_color = -1;
	window->map->ceiling_color = -1;
	//put it here for now
	if (!(image = malloc(sizeof(t_image))))
		ft_exit("Malloc failed\n");
	ft_bzero(image, sizeof(t_image));
	if (!(image->img = mlx_new_image(window->mlx, 640, 480)))
		ft_exit("mlx_new_image failed\n");
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length,
                                 &image->endian);
	image->width = 640;
	image->height = 480;
	window->image = image;
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

int			init_player(t_window *window)
{
	if (!(window->player = malloc(sizeof(t_player))))
		return (-1);
	ft_bzero(window->player, sizeof(t_player));
	window->player->pos_x = -20.0;
	window->player->pos_y = -20.0;
	window->player->speed = 0.10;
	window->player->dir_x = 1.0;
	window->player->dir_y = 0.0;
	window->player->plane_x = -20.0;
	window->player->plane_y = -20.0;
	window->player->rotate_speed = 0.10;
	window->player->cam_height = 1.0;
	window->player->health = 20;
	return (0);
}
