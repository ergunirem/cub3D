/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 11:32:39 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/03/07 22:52:17 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_window *window)
{
	char **map;
	t_player *p;

	map = window->map->map_array;
	p = window->player;
	if (map[(int)(p->pos_y)][(int)(p->pos_x + p->dir_x * p->move_speed)] == '0')
		p->pos_x += p->dir_x * p->move_speed;
	if (map[(int)(p->pos_y + p->dir_y * p->move_speed)][(int)(p->pos_x)] == '0')
		p->pos_y += p->dir_y * p->move_speed;
}

void	move_backward(t_window *window)
{
	char **map;
	t_player *p;

	map = window->map->map_array;
	p = window->player;
	if (map[(int)(p->pos_y)][(int)(p->pos_x - p->dir_x * p->move_speed)] == '0')
		p->pos_x -= p->dir_x * p->move_speed;
	if (map[(int)(p->pos_y - p->dir_y * p->move_speed)][(int)(p->pos_x)] == '0')
		p->pos_y -= p->dir_y * p->move_speed;
}

void	move_left(t_window *window)
{
	char **map;
	t_player *p;

	map = window->map->map_array;
	p = window->player;
	if (map[(int)p->pos_y][(int)(p->pos_x - p->plane_x * p->move_speed)] == '0')
		p->pos_x -= p->plane_x * p->move_speed;
	if (map[(int)(p->pos_y - p->plane_y * p->move_speed)][(int)p->pos_x] == '0')
		p->pos_y -= p->plane_y * p->move_speed;
}

void	move_right(t_window *window)
{
	char **map;
	t_player *p;

	map = window->map->map_array;
	p = window->player;
	if (map[(int)p->pos_y][(int)(p->pos_x + p->plane_x * p->move_speed)] == '0')
		p->pos_x += p->plane_x * p->move_speed;
	if (map[(int)(p->pos_y + p->plane_y * p->move_speed)][(int)p->pos_x] == '0')
		p->pos_y += p->plane_y * p->move_speed;
}

void	look_left(t_window *window)
{
	double old_dir_x;
	double old_plane_x;
	t_player *p;

	p = window->player;

	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(-p->rotate_speed) - p->dir_y * sin(-p->rotate_speed);
	p->dir_y = old_dir_x * sin(-p->rotate_speed) + p->dir_y * cos(-p->rotate_speed);
	p->plane_x = p->plane_x * cos(-p->rotate_speed) - p->plane_y * sin(-p->rotate_speed);
	p->plane_y = old_plane_x * sin(-p->rotate_speed) + p->plane_y * cos(-p->rotate_speed);
}

void	look_right(t_window *window)
{
	double old_dir_x;
	double old_plane_x;
	t_player *p;

	p = window->player;
	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(p->rotate_speed) - p->dir_y * sin(p->rotate_speed);
	p->dir_y = old_dir_x * sin(p->rotate_speed) + p->dir_y * cos(p->rotate_speed);
	p->plane_x = p->plane_x * cos(p->rotate_speed) - p->plane_y * sin(p->rotate_speed);
	p->plane_y = old_plane_x * sin(p->rotate_speed) + p->plane_y * cos(p->rotate_speed);
}

void	set_start_camera(t_window *window, double dir_x, double plane_x, double plane_y)
{
	window->player->dir_x = dir_x;
	window->player->plane_x = plane_x;
	window->player->plane_y = plane_y;
}
