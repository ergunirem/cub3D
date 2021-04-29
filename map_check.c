/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 17:49:35 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/29 18:11:15 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_first_char_in_row(char *row, t_window *window)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (row[i] == ' ')
			i++;
		if (row[i] == '1')
			break ;
		if (row[i] == '0')
			ft_exit("Map is not surrounded by walls\n", window);
	}
}

static void	check_last_char_in_row(char *row, t_window *window)
{
	int	i;

	i = window->map->max_col;
	while (i > 0)
	{
		if (row[i] == ' ' || row[i] == '\0')
			i--;
		if (row[i] == '1')
			break ;
		if (row[i] == '0')
			ft_exit("Map is not surrounded by walls\n", window);
	}
}

void	check_borders(t_window *window)
{
	int		i;
	char	*row;

	i = 0;
	while (i < window->map->max_row)
	{
		row = window->map->map_array[i];
		check_first_char_in_row(row, window);
		check_last_char_in_row(row, window);
		i++;
	}
	check_top(window);
	check_bottom(window);
}
