/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_sprites.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 21:18:14 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/28 03:40:43 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_sprites_num(t_window *window)
{
	int		i;
	int		j;
	char	**map;

	map = window->map->map_array;
	i = 0;
	while (i < window->map->max_row)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				window->spr_num++;
			}
			j++;
		}
		i++;
	}
}

static void	create_spr_arr(t_window *window)
{
	int	i;

	window->spr = (double**)malloc(sizeof(double*) * window->spr_num);
	if (!window->spr)
		ft_exit("malloc failed in create_spr_arr\n", window);
	i = 0;
	while (i < window->spr_num)
	{
		window->spr[i] = (double*)malloc(sizeof(double) * 3);
		if (!window->spr[i])
			ft_exit("malloc failed in create_spr_arr\n", window);
		i++;
	}
}

static void	fill_spr_arr(t_window *window)
{
	int		i;
	int		j;
	int		num;
	char	**map;

	map = window->map->map_array;
	i = 0;
	num = 0;
	while (i < window->map->max_row)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				window->spr[num][0] = j;
				window->spr[num][1] = i;
				window->spr[num][2] = 0;
				num++;
			}
			j++;
		}
		i++;
	}
}

void	get_sprites(t_window *window)
{
	window->spr_num = 0;
	get_sprites_num(window);
	if (window->spr_num == 0)
		return ;
	create_spr_arr(window);
	fill_spr_arr(window);
}
