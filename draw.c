/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 17:56:22 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/23 02:28:56 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_ray(t_window *window, t_ray *ray)
{
	t_player	*player;

	player = window->player;
	init_ray(ray, player, window);
	next_step(ray, player);
	while (ray->hit == 0)
	{
		get_wall_side(ray);
		if (window->map->map_array[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
		else if (window->map->map_array[ray->map_y][ray->map_x] == '2')
			handle_sprite(window, ray, window->s_list);
	}
	get_distance(ray, player, window);
	apply_textures(ray, window);
	ray->z_buffer[ray->pix] = ray->perp_wall_dist;
	color_vertical_line(window, window->map->ceiling_color, 0,
		ray->draw_start, ray->pix);
	color_vertical_line(window, window->map->floor_color, ray->draw_end,
		window->height, ray->pix);
	ray->pix++;
}

void	draw(t_window *window)
{
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		ft_exit("Malloc failed\n", window);
	ft_bzero(ray, sizeof(t_ray));
	ray->z_buffer = malloc(sizeof(double) * window->width);
	if (!ray->z_buffer)
		ft_exit("Malloc failed\n", window);
	ft_bzero(ray->z_buffer, sizeof(double) * window->width);
	while (ray->pix < window->width)
		cast_ray(window, ray);
	draw_sprites(window, ray);
	if (window->screenshot == 1)
	{
		window->screenshot = 0;
		create_bitmap(window);
		exit(0);
	}
	mlx_put_image_to_window(window->mlx, window->win, window->image->img, 0, 0);
	free(ray->z_buffer);
	free(ray);
}
