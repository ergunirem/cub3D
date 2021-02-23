/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 10:20:45 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/02/23 21:16:43 by icikrikc      ########   odam.nl         */
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
	{
		parse_map(window, line, map_list);
		//printf("%s\n", ft_lstlast(map_list)->content);
		//printf("%s\n", map_list->content);
	}

}

void		is_map_valid(t_window *window, t_list *map_list)
{
	int map_height;

	map_height = ft_lstsize(map_list);
	printf("h: %d\n", map_height);
}

int			parse(char *file_name, t_window *window)
{
	int ret_val;
	int fd;
	char *line;
	t_list *map_list;

	map_list = NULL;

	fd = open(file_name, O_RDONLY);
	ret_val = 1;
	line = NULL;
	while (ret_val > 0)
	{
		ret_val = get_next_line(fd, &line);
		if (ret_val == -1)
			exit_w_message("get next line failed\n", 1, window);
		// printf("%s\n", line);
		else if (ret_val != 0)
			parse_line(window, line, map_list);
		free(line);
	}
	//printf("%s\n", map_list->content);
	//printf("%s\n", ft_lstlast(map_list)->content);

	//is_map_valid(window, *map_list);
	// while (map_list != NULL)
	// {
	// 	printf("%s\n", map_list->content);
	// 	map_list = map_list->next;
	// }
	close(fd);
	// free(line); //double-free error? but what about the last line ret val is 0?
	return (0);
}
