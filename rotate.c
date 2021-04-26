/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 17:08:30 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/26 16:41:52 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	look_left(t_window *window)
{
	double		dir_x;
	double		plane_x;
	t_player	*p;

	p = window->player;
	dir_x = p->dir_x;
	plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(-p->rotate_speed)
		- p->dir_y * sin(-p->rotate_speed);
	p->dir_y = dir_x * sin(-p->rotate_speed)
		+ p->dir_y * cos(-p->rotate_speed);
	p->plane_x = p->plane_x * cos(-p->rotate_speed)
		- p->plane_y * sin(-p->rotate_speed);
	p->plane_y = plane_x * sin(-p->rotate_speed)
		+ p->plane_y * cos(-p->rotate_speed);
}

void	look_right(t_window *window)
{
	double		dir_x;
	double		plane_x;
	t_player	*p;

	p = window->player;
	dir_x = p->dir_x;
	plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(p->rotate_speed)
		- p->dir_y * sin(p->rotate_speed);
	p->dir_y = dir_x * sin(p->rotate_speed)
		+ p->dir_y * cos(p->rotate_speed);
	p->plane_x = p->plane_x * cos(p->rotate_speed)
		- p->plane_y * sin(p->rotate_speed);
	p->plane_y = plane_x * sin(p->rotate_speed)
		+ p->plane_y * cos(p->rotate_speed);
}

void	set_camera(t_window *win, double dir_x, double plane_x, double plane_y)
{
	win->player->dir_x = dir_x;
	win->player->plane_x = plane_x;
	win->player->plane_y = plane_y;
}
