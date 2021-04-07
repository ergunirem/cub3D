/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 17:56:22 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/07 22:34:30 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_window *window)
{
	t_ray *ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		ft_exit("Malloc failed\n");
	ft_bzero(ray, sizeof(t_ray));
	if (!(ray->z_buffer = malloc(sizeof(double) * window->width)))
		ft_exit("Malloc failed\n");
	ft_bzero(ray->z_buffer, sizeof(double) * window->width);
	while (ray->pix < window->width)
		cast_ray(window, ray);
	//sprites are drawn after walls&floor&ceiling are drawn - the ray-casting loop ends
	// printf("pl:%f\n", window->player->pos_x);
	draw_sprites(window, ray);
		// return (ERROR);
	// if (window->screenshot == 1)
	// {
	// 	window->screenshot = 0;
	// 	create_bitmap(window->img, "cub3D");
	// 	exit(0);
	// }
	mlx_put_image_to_window(window->mlx, window->win, window->image->img, 0, 0);
	free(ray->z_buffer);
	free(ray);
}
