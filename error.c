/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 12:42:41 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/02/23 13:25:33 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_w_message(char *msg, int window_open, t_window *window)
{
	// if(window_open == 0)
	// 	mlx_destroy_window(window->mlx, window->win);
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(msg, 1);
	exit(0);
}
