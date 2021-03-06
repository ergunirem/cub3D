/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paint.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 18:11:03 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/03/06 23:30:38 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_vertical_line(t_window *window, int color, int draw_start, int draw_end, int x_ray_pix)
{
	if (draw_start >= 0)
	{
		while (draw_start < draw_end)
		{
			my_mlx_pixel_put(window->image, x_ray_pix, draw_start, color);
			draw_start++;
		}
	}
}
