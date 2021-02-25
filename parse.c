/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 10:20:45 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/02/25 22:24:36 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void parse_check(t_window *window)
{
	if (window->width <= 0 || window->height <= 0)
		exit_w_message("invalid or no resolution\n", 1, window);
	if(window->map->floor_color < 0 || window->map->ceiling_color < 0)
		exit_w_message("invalid or no color\n", 1, window);
	if(window->map->floor_color == window->map->ceiling_color)
		exit_w_message("same colour for floor&ceiling\n", 1, window);
	if (window->textures->north->endian == -1)
		exit_w_message("no north texture path\n", 1, window);
	if (window->textures->south->endian == -1)
		exit_w_message("no south texture path\n", 1, window);
	if (window->textures->east->endian == -1)
		exit_w_message("no east texture path\n", 1, window);
	if (window->textures->west->endian == -1)
		exit_w_message("no west texture path\n", 1, window);
	if (window->textures->sprite->endian == -1)
		exit_w_message("no sprite texture path\n", 1, window);
}

static void	parse_line(t_window *window, char *line, t_list *map_list)
{
	while(ft_iswhitespace(*line))
		line++;
	if (*line == '\0' && window->map->map_started == TRUE)
		exit_w_message("empty line inside map\n", 1, window);
	else if (*line == '\0' && window->map->map_started == FALSE)
		return ;
	else if (*line == 'R')
		parse_resolution(window, line + 1);
	else if (*line == 'F' || *line == 'C')
		parse_color(window, line);
	else if (*line == 'N' && *(line + 1) == 'O')
	 	parse_texture(window, window->textures->north, line + 2);
	else if (*line == 'S' && *(line + 1) == 'O')
		parse_texture(window, window->textures->south, line + 2);
	else if (*line == 'W' && *(line + 1) == 'E')
		parse_texture(window, window->textures->west, line + 2);
	else if (*line == 'E' && *(line + 1) == 'A')
		parse_texture(window, window->textures->east, line + 2);
	else if (*line == 'S' && *(line + 1) == ' ')
		parse_texture(window, window->textures->sprite, line + 2);
	else if (*line == '1') //any other char (02NESW)
		parse_map(window, line, map_list);
}

int			parse(char *file_name, t_window *window)
{
	int ret_val;
	int fd;
	char *line;
	t_list *map_list;

	fd = open(file_name, O_RDONLY);
	ret_val = 1;
	line = NULL;
	map_list = ft_lstnew("map");
	while (ret_val > 0)
	{
		ret_val = get_next_line(fd, &line);
		if (ret_val == -1)
			exit_w_message("get next line failed\n", 1, window);
		else if (ret_val > 0)
			parse_line(window, line, map_list);
		free(line);
	}
	parse_check(window);
	if (ft_lstsize(map_list) == 1)
		exit_w_message("no map provided\n", 1, window);
	save_map(window, window->map, map_list);
	check_start_pos(window);
	//printf("r: %d | c: %d\n", window->map->row_pos, window->map->col_pos);
	check_map(window, window->map->row_pos, window->map->col_pos);
	int i = 0;
	while (i < window->map->max_row)
	{
		printf("%s\n", window->map->map_array[i]);
		i++;
	}
	//ft_lstfree(&map_list); //bus error :(
	close(fd);
	// free(line); //double-free error? but what about the last line ret val is 0?
	return (0);
}
