/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pixel_funcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 21:59:01 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/29 18:31:15 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	my_mlx_pixel_get(t_image *img, int x, int y)
{
	int		color;
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	my_mlx_pixel_set(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	color_vertical_line(t_window *window, int draw_start,
	int draw_end, int x_ray_pix)
{
	int	color;

	if (draw_start == 0)
		color = window->map->ceiling_color;
	if (draw_end == window->height)
		color = window->map->floor_color;
	if (draw_start >= 0)
	{
		while (draw_start < draw_end)
		{
			my_mlx_pixel_set(window->image, x_ray_pix, draw_start, color);
			draw_start++;
		}
	}
}
