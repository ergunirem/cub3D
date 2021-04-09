/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray-casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/06 23:27:20 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/09 10:56:25 by icikrikc      ########   odam.nl         */
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

void	cast_ray(t_window *window, t_ray *ray)
{
	t_player	*player;

	player = window->player;
	init_ray(ray, player, window);
	next_step(ray, player);
	while (ray->hit == 0)
	{
		get_wall_side(ray);
		// printf("lst: %p\n", window->s_info->s_list->next);
		if (window->map->map_array[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
		else if (window->map->map_array[ray->map_y][ray->map_x] == '2')
			handle_sprite(window, ray, window->s_info->s_list);
	}
	get_distance(ray, player, window);
	apply_textures(ray, window);
	ray->z_buffer[ray->pix] = ray->perp_wall_dist;
	color_vertical_line(window, window->map->ceiling_color, 0, ray->draw_start, ray->pix);
	color_vertical_line(window, window->map->floor_color, ray->draw_end, window->height, ray->pix);
	ray->pix++;
}

