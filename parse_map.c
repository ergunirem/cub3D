/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 15:30:38 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/03/05 15:58:20 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(t_window *window, char *line, t_list *map_list)
{
	int		i;
	t_list	*new;

	window->map->map_started = TRUE;
	i = 0;
	while (line[i])
	{
		if (ft_strchr("012NSEW ", line[i]) == NULL)
			exit_w_message("invalid char inside map\n", 1, window);
		i++;
	}
	if (window->map->max_col < ft_strlen(line))
		window->map->max_col = ft_strlen(line);
	new = ft_lstnew(ft_strdup(line));
	if (!new)
		exit_w_message("ft_lstnew failed\n", 1, window);
	ft_lstadd_back(&map_list, new);
}

void	save_map(t_window *window, t_map *map, t_list *map_list)
{
	char	*str;
	int		i;
	int		j;

	map->max_row = ft_lstsize(map_list) - 1;
	map->map_array = (char **)malloc(sizeof(char *) * map->max_row);
	if (!map->map_array)
		exit_w_message("save_map malloc failed\n", 1, window);
	map_list = map_list->next;
	i = 0;
	while (map_list != NULL)
	{
		str = map_list->content;
		map->map_array[i] = ft_calloc(map->max_col + 1, sizeof(char));
		if (!map->map_array[i])
			exit_w_message("save_map malloc failed\n", 1, window);
		j = 0;
		while (str[j] != '\0')
		{
			map->map_array[i][j] = str[j];
			j++;
		}
		// map->map_array[i][j] = '\0'; // do i need this calloc already?
		// j++;
		// while (j < map->max_col)
		// {
		// 	map->map_array[i][j] = ' ';
		// 	j++;
		// }
		// map->map_array[i][j] = '\0';
		map_list = map_list->next;
		i++;
	}
}

static void	set_start_camera(t_window *window, double dir_x, double plane_x, double plane_y)
{
	window->player->dir_x = dir_x;
	window->player->plane_x = plane_x;
	window->player->plane_y = plane_y;
}

static void	set_start_pos(t_window *window, char pos, int j, int i)
{
	if (pos == 'E')
	{
		window->player->dir_y = 0.0;
		set_start_camera(window, 1.0, 0.0, 0.66);
	}
	else if (pos == 'W')
	{
		window->player->dir_y = 0.0;
		set_start_camera(window, -1.0, 0.0, -0.66);
	}
	else if (pos == 'N')
	{
		window->player->dir_y = -1.0;
		set_start_camera(window, 0.0, 0.66, 0.0);
	}
	else if (pos == 'S')
	{
		window->player->dir_y = 1.0;
		set_start_camera(window, 0.0, -0.66, 0.0);
	}
	window->player->pos_x = (double)j + 0.5;
	window->player->pos_y = (double)i + 0.5;
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
					exit_w_message("Multiple starting positions\n", 1, window);
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
 * Then by calling func recursively player can either go south or north
 * or east or west
*/

void	check_map(t_window *window, int row, int col)
{
	t_map	*map;

	map = window->map;
	if (row < 0 || col < 0 || row > map->max_row || col > map->max_col)
		return ;
	if (map->map_array[row][col] == '1' || map->map_array[row][col] == 'X')
		return ;
	if (map->map_array[row][col] == ' ')
		exit_w_message("Map is not surrounded by walls\n", 1, window);
	if ((row == 0 || col == 0) && map->map_array[row][col] == '0')
		exit_w_message("Map is not surrounded by walls\n", 1, window);
	if ((row == map->max_row - 1 || col == map->max_col - 1)
		&& map->map_array[row][col] == '0')
		exit_w_message("Map is not surrounded by walls\n", 1, window);
	map->map_array[row][col] = 'X';
	check_map(window, row + 1, col);
	check_map(window, row - 1, col);
	check_map(window, row, col + 1);
	check_map(window, row, col - 1);
	return ;
}
