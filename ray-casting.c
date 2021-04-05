/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray-casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/06 23:27:20 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/05 22:00:53 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Calculate distance projected on camera direction
(Euclidean distance will give fisheye effect!) */


static void	get_distance(t_ray *ray, t_player *player, t_window *window)
{
	if (ray->side == 0 || ray->side == 1)
		ray->perp_wall_dist = (ray->map_x - player->pos_x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->pos_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	ray->line_height = (int)(window->height / ray->perp_wall_dist);
	ray->draw_start = (-ray->line_height / 2 + ((window->height / 2)
			* window->player->cam_height));
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2 + ((window->height / 2)
		* window->player->cam_height));
	if (ray->draw_end >= window->height)
		ray->draw_end = window->height - 1;
}

static void	get_wall_side(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->del_dist_x;
		ray->map_x += ray->step_x;
		if (ray->step_x == 1)
			ray->side = 0;
		else if (ray->step_x == -1)
			ray->side = 1;
	}
	else
	{
		ray->side_dist_y += ray->del_dist_y;
		ray->map_y += ray->step_y;
		if (ray->step_y == 1)
			ray->side = 2;
		else if (ray->step_y == -1)
			ray->side = 3;
	}
}

static void	next_step(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->del_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->del_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->del_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->del_dist_y;
	}
}

static void	init_ray(t_ray *ray, t_player *player, t_window *window)
{
	ray->cam_x = (2 * ray->pix) / (double)window->width - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->cam_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->cam_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->del_dist_x = fabs(1 / ray->ray_dir_x);
	ray->del_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

t_image	*designate_tex(t_ray *ray, t_window *window, double wall_x)
{
	t_image	*img;

	img = window->textures->north;
	if (ray->side == 1)
		img = window->textures->south;
	if (ray->side == 2)
		img = window->textures->east;
	if (ray->side == 3)
		img = window->textures->west;
	return (img);
}

void	apply_textures(t_ray *ray, t_window *window)
{
	t_player	*p;
	t_tex		*tex;
	t_image		*img;
	int			y;
	int			color;

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
	tex->step = 1.0 * 64 / ray->line_height;
	tex->tex_pos = (ray->draw_start - window->height / 2 + ray->line_height / 2) * tex->step;

	// printf("y: %d ", img->height);
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

void	cast_ray(t_window *window, t_ray *ray)
{
	t_player	*player;

	player = window->player;
	init_ray(ray, player, window);
	next_step(ray, player);
	while (ray->hit == 0)
	{
		get_wall_side(ray);
		if (window->map->map_array[ray->map_y][ray->map_x] == '1') // > '0'?
			ray->hit = 1;
		// else if (window->map->map_array[ray->map_y][ray->map_x] == '2')
		// 	is_sprite(ray, window);
	}
	get_distance(ray, player, window);
	apply_textures(ray, window);
	ray->z_buffer[ray->pix] = ray->perp_wall_dist;
	color_vertical_line(window, 0x0000000, 0, ray->draw_start, ray->pix);
	color_vertical_line(window, 0x0000000, ray->draw_end, window->height, ray->pix);
	ray->pix++;
}

