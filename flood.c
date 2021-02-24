/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 20:38:57 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/02/24 21:27:59 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(t_window *window, int row, int col)
{
	t_map *map;

	map = window->map;
	if (row < 0 || col < 0 || row > map->max_row) /* || col > MAX_WIDTH Out of bounds */
		return ;

	if(map->map_array[row][col] == '1' || map->map_array[row][col] == 'X') // if there is a wall or if i have been there
		return ;

	if(map->map_array[row][col] == ' ') // if it's a space throw error
		exit_w_message("Invalid map\n", 1, window) ;

	map->map_array[row][col] = 'X'; // mark the point so that I know if I passed through it.
	flood_fill(window, row + 1, col);  // then i can either go south
	flood_fill(window, row - 1, col);  // or north
	flood_fill(window, row, col + 1);  // or east
	flood_fill(window, row, col - 1);  // or west

	return ;
}
