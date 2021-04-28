/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 12:42:41 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/28 03:49:42 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map_arr(t_window *window)
{
	char	**arr;
	int		i;

	arr = window->map->map_array;
	i = 0;
	while (i < window->map->max_row)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	free_tex(t_window *window)
{
	if (window->textures->north)
		mlx_destroy_image(window->mlx, window->textures->north->img);
	if (window->textures->south)
		mlx_destroy_image(window->mlx, window->textures->south->img);
	if (window->textures->east)
		mlx_destroy_image(window->mlx, window->textures->east->img);
	if (window->textures->west)
		mlx_destroy_image(window->mlx, window->textures->west->img);
	if (window->textures->sprite)
		mlx_destroy_image(window->mlx, window->textures->sprite->img);
	if (window->textures)
		free(window->textures);
}

static void	free_spr(t_window *window)
{
	int	i;

	i = 0;
	while (i < window->spr_num)
	{
		if (window->spr[i])
			free(window->spr[i]);
		i++;
	}
	free(window->spr);
}

void	ft_exit(char *msg, t_window *window)
{
	if (msg[0] != 'e' && msg[1] != 's' && msg[1] != 'c')
		ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(msg, 1);
	if (window->mlx && window->win)
		mlx_destroy_window(window->mlx, window->win);
	if (window->map->arr_malloc == 1)
		free_map_arr(window);
	if (window->map_malloc == 1)
		free(window->map);
	if (window->player_malloc == 1)
		free(window->player);
	if (window->keys_malloc == 1)
		free(window->keys);
	if (window->image_malloc == 1)
		free(window->image);
	if (window->spr)
		free_spr(window);
	// if (window->textures)
	// 	free_tex(window);
	exit(0);
}

void	ft_exit_basic(char *msg)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(msg, 1);
	exit(0);
}
