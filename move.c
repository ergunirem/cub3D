/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 11:32:39 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/03/08 17:10:51 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_window *window)
{
	char		**map;
	t_player	*p;

	map = window->map->map_array;
	p = window->player;
	if (map[(int)(p->pos_y)][(int)(p->pos_x + p->dir_x * p->move_speed)] == '0')
		p->pos_x += p->dir_x * p->move_speed;
	if (map[(int)(p->pos_y + p->dir_y * p->move_speed)][(int)(p->pos_x)] == '0')
		p->pos_y += p->dir_y * p->move_speed;
}

void	move_backward(t_window *window)
{
	char		**map;
	t_player	*p;

	map = window->map->map_array;
	p = window->player;
	if (map[(int)(p->pos_y)][(int)(p->pos_x - p->dir_x * p->move_speed)] == '0')
		p->pos_x -= p->dir_x * p->move_speed;
	if (map[(int)(p->pos_y - p->dir_y * p->move_speed)][(int)(p->pos_x)] == '0')
		p->pos_y -= p->dir_y * p->move_speed;
}

void	move_left(t_window *window)
{
	char		**map;
	t_player	*p;

	map = window->map->map_array;
	p = window->player;
	if (map[(int)p->pos_y][(int)(p->pos_x - p->plane_x * p->move_speed)] == '0')
		p->pos_x -= p->plane_x * p->move_speed;
	if (map[(int)(p->pos_y - p->plane_y * p->move_speed)][(int)p->pos_x] == '0')
		p->pos_y -= p->plane_y * p->move_speed;
}

void	move_right(t_window *window)
{
	char		**map;
	t_player	*p;

	map = window->map->map_array;
	p = window->player;
	if (map[(int)p->pos_y][(int)(p->pos_x + p->plane_x * p->move_speed)] == '0')
		p->pos_x += p->plane_x * p->move_speed;
	if (map[(int)(p->pos_y + p->plane_y * p->move_speed)][(int)p->pos_x] == '0')
		p->pos_y += p->plane_y * p->move_speed;
}
