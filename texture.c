/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 15:20:14 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/28 15:02:54 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*designate_tex(t_ray *ray, t_window *window, double wall_x)
{
	if (ray->side == 0)
		return (&window->textures->tex[0]);
	else if (ray->side == 1)
		return (&window->textures->tex[1]);
	else if (ray->side == 2)
		return (&window->textures->tex[2]);
	else
		return (&window->textures->tex[3]);
}

static void	draw_textures(t_ray *ray, t_window *window, t_image *img)
{
	t_player	*p;
	t_tex		*tex;
	int			color;
	int			y;

	tex = window->textures;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->tex_y = (int)tex->tex_pos & (64 - 1);
		tex->tex_pos += tex->step;
		color = my_mlx_pixel_get(img, tex->tex_x, tex->tex_y);
		my_mlx_pixel_set(window->image, ray->pix, y, color);
		y++;
	}
}

void	apply_textures(t_ray *ray, t_window *window)
{
	t_player	*p;
	t_tex		*tex;
	t_image		*img;
	int			y;

	p = window->player;
	tex = window->textures;
	if (window->map->map_array[ray->map_y][ray->map_x] == '1')
		img = designate_tex(ray, window, tex->wall_x);
	if (ray->side == 0 || ray->side == 1)
		tex->wall_x = p->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		tex->wall_x = p->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	tex->wall_x -= floor((tex->wall_x));
	tex->tex_x = (int)(tex->wall_x * (double)(img->width));
	if ((ray->side == 0 || ray->side == 2) && ray->ray_dir_x > 0)
		tex->tex_x = img->width - tex->tex_x - 1;
	if ((ray->side == 1 || ray->side == 3) && ray->ray_dir_y < 0)
		tex->tex_x = img->width - tex->tex_x - 1;
	// printf("tex-height: %d\n", tex->height);
	tex->step = 1.0 * 64 / ray->line_height;
	tex->tex_pos = (ray->draw_start - window->height / 2
			+ ray->line_height / 2) * tex->step;
	draw_textures(ray, window, img);
}
