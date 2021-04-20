/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 12:42:41 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/20 01:57:26 by icikrikc      ########   odam.nl         */
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

void	free_tex(t_window *window)
{
	if (window->textures->north)
		free(window->textures->north);
	// if (window->textures->south)
	// 	free(window->textures->south);
	// if (window->textures->east)
	// 	free(window->textures->east);
	// if (window->textures->west)
	// 	free(window->textures->west);
	// if (window->textures->sprite)
	// 	free(window->textures->sprite);
	// if (window->textures)
	// 	free(window->textures);
}

void	ft_exit(char *msg, t_window *window)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(msg, 1);
	// if (window->mlx && window->win)
	// 	mlx_destroy_window(window->mlx, window->win);
	// if (window->image)
	// 	mlx_destroy_image(window->mlx, window->image);
	// if (window->player)
	// 	free(window->player);
	// if (window->keys)
	// 	free(window->keys);
	// //segv w/lstfree!
	// // if (window->s_info->s_list)
	// // 	my_lstfree(window->s_info->s_list);
	// if(window->s_info)
	// 	free(window->s_info);
	// if (window->map)
	// 	free(window->map);
	// free_tex(window);
	// if (window)
	// 	free(window);
	exit(0);
}
