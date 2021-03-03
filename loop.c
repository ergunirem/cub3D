/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 18:11:03 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/03/03 20:47:28 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Calculate distance projected on camera direction
//(Euclidean distance will give fisheye effect!)
static void	get_distance(t_ray *ray, t_player *player, t_window *win_infos)
{
	if (ray->side == 0 || ray->side == 1)
		ray->perp_wall_dist = (ray->map_x - player->pos_x + (1 - ray->step_x) / 2)
		/ ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->pos_y + (1 - ray->step_y) / 2)
		/ ray->ray_dir_y;
	ray->line_height = (int)(win_infos->height / ray->perp_wall_dist);
	ray->draw_start = (-ray->line_height / 2 + ((win_infos->height / 2)
		* win_infos->player->cam_height));
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2 + ((win_infos->height / 2)
		* win_infos->player->cam_height));
	if (ray->draw_end >= win_infos->height)
		ray->draw_end = win_infos->height - 1;
}

/*
 * jump to next map square, OR in x-direction, OR in y-direction
*/
static void	get_wall_side(t_ray *ray)
{
	//Each time, either it jumps a square in x-direction (with stepX)
	//or a square in the y-direction (with stepY)

	//sideDistX & sideDistY get incremented with delDistX with every jump in their direction,
	//mapX & mapY get incremented with stepX and stepY respectively.
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

static void	hit(t_ray *ray,t_window *win_infos)
{
	//increments ray with 1 square every time, until a wall is hit.
	while (ray->hit == 0)
	{
		//When the ray has hit a wall, the loop ends, and then we'll know
		//whether an x-side or y-side of a wall was hit in the variable "side",
		//and what wall was hit with mapX and mapY
		get_wall_side(ray);
		if (win_infos->map->map_array[ray->map_y][ray->map_x] > '0'
			&& win_infos->map->map_array[ray->map_y][ray->map_x] != '2')
			ray->hit = 1;
		// else if (win_infos->map->map_array[ray->map_y][ray->map_x] == '2')
		// 	is_sprite(ray, win_infos);
	}
}

//calculations for both x and y
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

static void init_ray(t_ray *ray, t_player *player, t_window *window)
{
	//calculate direction of the ray:
	//sum of player's direction vector * part of player's plane vector
	ray->cam_x = (2 * ray->pix) / (double)window->width - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->cam_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->cam_x;
	//ray starts at the position of the player
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	//simplified calculation of pythagoras
	ray->del_dist_x = fabs(1 / ray->ray_dir_x);
	ray->del_dist_y = fabs(1 / ray->ray_dir_y);
	//make hit zero so that when it's one the loop can end
	ray->hit = 0;
}

static void	cast_ray(t_window *window, t_ray *ray)
{
	t_player	*player;

	player = window->player;
	//calculate the direction of the ray
	init_ray(ray, player, window);
	//before DDA starts, some things have to be calculated:
	//which direction the DDA will jump one square and
	//the distance the ray has to travel from its starting point
	//to the first x-side and first y-side it comes across
	next_step(ray, player);
	//DDA starts: to end the loop when a wall/sprite is hit
	hit(ray, window);
	get_distance(ray, player, window);
	// ray->z_buffer[ray->pix] = ray->perp_wall_dist;
	// texturisation(ray, window);
	ray->pix++;
}

static void	draw(t_window *window)
{
	t_ray *ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		ft_exit("raycasting failed\n");
	ft_bzero(ray, sizeof(t_ray));
	//raycasting loop which goes per vertical stripe rather than per pixel
	while (ray->pix < window->width)
		cast_ray(window, ray);
	// if (!draw_sprite(ray, window))
	// 	return (ERROR);
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

int	handle_loop(t_window *window)
{
	draw(window);
	return (0);
}
