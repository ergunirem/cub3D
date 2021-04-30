/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_handle.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 15:30:38 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/30 02:17:16 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_map(t_window *window, t_map *map, t_list *map_list, int i)
{
	char	*str;
	int		j;

	map->map_array = (char **)malloc(sizeof(char *) * map->max_row);
	if (!map->map_array)
		ft_exit("save_map malloc failed\n", window);
	i = 0;
	while (map_list != NULL)
	{
		str = map_list->content;
		map->map_array[i] = ft_calloc(map->max_col + 1, sizeof(char));
		if (!map->map_array[i])
			ft_exit("save_map malloc failed\n", window);
		ft_memset(map->map_array[i], ' ', map->max_col);
		j = 0;
		while (str[j] != '\0')
		{
			map->map_array[i][j] = str[j];
			j++;
		}
		map->map_array[i][map->max_col] = '\0';
		free(map_list->content);
		map_list = map_list->next;
		i++;
	}
}

void	check_start_pos(t_window *window)
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
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (window->map->row_pos > 0 || window->map->col_pos > 0)
					ft_exit("Multiple starting positions\n", window);
				set_start_pos(window, map[i][j], j, i);
				map[i][j] = '0';
				window->map->row_pos = i;
				window->map->col_pos = j;
			}
			j++;
		}
		i++;
	}
}

/*
 * This function implements flood fiil alghorithm which is
 * one of the easiest and quickest way to check map validity
 * 1st if: for out of bounds
 * 2nd if: there is a wall or if i have been there
 * 3rd if: if it's a space, throw error
 * 4th and 5th if: if it's a zero on borders, throw error
 * Then, mark the point with 'X' so that I know if player passed through it.
 * Then by calling func recursively player can either go in 8 directions
*/

void	check_map(t_window *window, int row, int col)
{
	t_map	*map;
	char	**arr;

	map = window->map;
	arr = map->map_array;
	if (row < 0 || col < 0 || row > map->max_row || col > map->max_col)
		return ;
	if (arr[row][col] == '1' || arr[row][col] == 'X' || arr[row][col] == '2')
		return ;
	if (arr[row][col] == ' ')
		ft_exit("Map is not surrounded by walls\n", window);
	if ((row == 0 || col == 0) && arr[row][col] == '0')
		ft_exit("Map is not surrounded by walls\n", window);
	if ((row == map->max_row - 1 || col == map->max_col - 1)
		&& arr[row][col] == '0')
		ft_exit("Map is not surrounded by walls\n", window);
	arr[row][col] = 'X';
	check_map(window, row + 1, col);
	check_map(window, row - 1, col);
	check_map(window, row, col + 1);
	check_map(window, row, col - 1);
	check_map(window, row + 1, col + 1);
	check_map(window, row - 1, col - 1);
	check_map(window, row - 1, col + 1);
	check_map(window, row + 1, col - 1);
}

void	restore_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->max_row)
	{
		j = 0;
		while (j < map->max_col)
		{
			if (map->map_array[i][j] == 'X')
				map->map_array[i][j] = '0';
			j++;
		}
		i++;
	}
}
