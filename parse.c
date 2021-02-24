/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 10:20:45 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/02/24 21:48:47 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void parse_check(t_window *window)
// {
// 	if (window->width <= 0 || window->height <= 0)
// 		exit_w_message("Error\n Invalid resolution\n", 1, window);
// 	if(window->map->floor_color < 0 || window->map->ceiling_color < 0)
// 		exit_w_message("Error\n Invalid floor/ceiling color\n", 1, window);
// }

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
	else if (*line == 'S' && *(line + 1) != 'O')
		parse_texture(window, window->textures->sprite, line + 2);
	else if (*line == '1') //any other char (02NESW)
		parse_map(window, line, map_list);
}

void		save_map(t_window *window, t_map *map, t_list *map_list)
{
	char	*str;
	int		i;
	int		j;

	map->max_row = ft_lstsize(map_list) - 1; //printf("h: %d\n", map_height);
	map->map_array = (char **)malloc(sizeof(char *) * map->max_row);
	if (!map->map_array)
		exit_w_message("save_map malloc failed\n", 1, window);
	i = -1;
	while (map_list != NULL)
	{
		if (i > -1)
		{
			str = map_list->content;
			map->map_array[i] = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
			if (!map->map_array[i])
				exit_w_message("save_map malloc failed\n", 1, window);
			j = 0;
			while (str[j] != '\0')
			{
				map->map_array[i][j] = str[j];
				j++;
			}
			map->map_array[i][j] = '\0'; //printf("%s\n", map->map_array[i]);
		}
		map_list = map_list->next;
		i++;
	}
}

void		check_start_pos(t_window *window)
{
	int i = 0;
	int j;
	char	**map;

	map = window->map->map_array;
	while (i < window->map->max_row)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (window->map->row_pos > 0 || window->map->col_pos > 0)
					exit_w_message("More than one starting position\n", 1, window);
				window->map->row_pos = i;
				window->map->col_pos = j;
			}
			// printf("%s\n", map[i][j]);
			j++;
		}
		// printf("%s\n", map[i]);
		i++;
	}
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
	save_map(window, window->map, map_list);
	check_start_pos(window);
	printf("r: %d | c: %d\n", window->map->row_pos, window->map->col_pos);
	flood_fill(window, window->map->row_pos, window->map->col_pos);
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
