/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check_2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 18:10:22 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/29 18:10:31 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_first_row(t_window *window, int i)
{
	int	j;

	j = 1;
	while (j < window->map->max_row)
	{
		if (window->map->map_array[j][i] == ' ')
			j++;
		if (window->map->map_array[j][i] == '1')
			return (i + 1);
		if (window->map->map_array[j][i] == '0')
			ft_exit("Map is not surrounded by walls\n", window);
	}
	return (0);
}

static int	check_last_row(t_window *window, int i)
{
	int	j;

	j = window->map->max_row - 2;
	while (j > 0)
	{
		if (window->map->map_array[j][i] == ' ')
			j--;
		if (window->map->map_array[j][i] == '1')
			return (i + 1);
		if (window->map->map_array[j][i] == '0')
			ft_exit("Map is not surrounded by walls\n", window);
	}
	return (0);
}

void	check_top(t_window *window)
{
	int	i;

	i = 0;
	while (window->map->map_array[0][i] == ' ')
		i++;
	while (i < window->map->max_col - 1)
	{
		if (window->map->map_array[0][i] == '1')
			i++;
		if (window->map->map_array[0][i] == '0')
			ft_exit("Map is not surrounded by walls\n", window);
		if (window->map->map_array[0][i] == ' ')
			i = check_first_row(window, i);
		else
			i++;
	}
}

void	check_bottom(t_window *window)
{
	int	i;

	i = 0;
	while (window->map->map_array[window->map->max_row - 1][i] == ' ')
		i++;
	while (i < window->map->max_col - 1)
	{
		if (window->map->map_array[window->map->max_row - 1][i] == '1')
			i++;
		if (window->map->map_array[window->map->max_row - 1][i] == '0')
			ft_exit("Map is not surrounded by walls\n", window);
		if (window->map->map_array[window->map->max_row - 1][i] == ' ')
			i = check_last_row(window, i);
		else
			i++;
	}
}
