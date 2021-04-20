/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_two.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/19 19:19:52 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/20 16:37:57 by icikrikc      ########   odam.nl         */
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
	if (!image->img)
		ft_exit("mlx_new_image failed\n", window);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	image->width = window->width;
	image->height = window->height;
	window->image = image;
}

void	init_sprite_info(t_window *window)
{
	t_sprite *s_list;

	window->s_info = malloc(sizeof(t_sprite_info));
	if (!window->s_info)
		ft_exit("Malloc failed\n", window);
	ft_bzero(window->s_info, sizeof(t_sprite_info));
	window->s_info->s_list = s_list;
	window->s_info->s_list->next = NULL;
	// window->s_info->s_list = (t_sprite *)malloc(sizeof(t_sprite));
	// if (!window->s_info->s_list)
	// 	ft_exit("Malloc failed\n", window);
	// window->s_info->s_list->x = -1;
	// window->s_info->s_list->y = -1;
	// window->s_info->s_list->next = NULL;
	window->s_info->num_sprites = 0;
}
