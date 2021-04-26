/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 12:42:41 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/26 02:31:12 by icikrikc      ########   odam.nl         */
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

static void	free_tex(t_window *window)
{
	if (window->textures->north->endian != -1)
		free(window->textures->north);
	// if (window->textures->south->endian != -1)
	// 	free(window->textures->south);
	// if (window->textures->east->endian != -1)
	// 	free(window->textures->east);
	// if (window->textures->west->endian != -1)
	// 	free(window->textures->west);
	// if (window->textures->sprite->endian != -1)
	// 	free(window->textures->sprite);
	if (window->textures)
		free(window->textures);
}

void	ft_exit(char *msg, t_window *window)
{
	if(msg[0] != 'e' && msg[1] != 's' && msg[1] != 'c')
		ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(msg, 1);
	if (window->mlx && window->win)
		mlx_destroy_window(window->mlx, window->win);
	if (window->player_malloc == 1)
		free(window->player);
	if (window->keys_malloc == 1)
		free(window->keys);
	if (window->image_malloc == 1)
	{
		// if (window->image)
		// 	mlx_destroy_image(window->mlx, window->image);
		free(window->image);
	}
	// //segv w/lstfree!
	// // if (window->s_info->s_list)
	// // 	my_lstfree(window->s_info->s_list);
	// if(window->s_info)
	// 	free(window->s_info);
	// if (window->map)
	// 	free(window->map);
	if (window->textures)
		free_tex(window);
	exit(0);
}

void	ft_exit_basic(char *msg)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(msg, 1);
	exit(0);
}
