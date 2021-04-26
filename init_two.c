/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_two.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/19 19:19:52 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/26 12:58:05 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	init_sprite_list(t_window *window)
{
	window->s_list = malloc(sizeof(t_sprite));
	if (!window->s_list)
		ft_exit("Malloc failed\n", window);
	ft_bzero(window->s_list, sizeof(t_sprite));
	window->s_list->x = -1;
	window->s_list->y = -1;
	window->s_list->next = NULL;
}
