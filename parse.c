/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 10:20:45 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/26 12:45:53 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_check(t_window *window)
{
	if (window->width <= 0 || window->height <= 0)
		ft_exit("invalid or no resolution\n", window);
	if (window->map->floor_color < 0 || window->map->ceiling_color < 0)
		ft_exit("invalid or no color\n", window);
	if (window->map->floor_color == window->map->ceiling_color)
		ft_exit("same colour for floor&ceiling\n", window);
	if (window->textures->north->endian == -1)
		ft_exit("no north texture path\n", window);
	if (window->textures->south->endian == -1)
		ft_exit("no south texture path\n", window);
	if (window->textures->east->endian == -1)
		ft_exit("no east texture path\n", window);
	if (window->textures->west->endian == -1)
		ft_exit("no west texture path\n", window);
	if (window->textures->sprite->endian == -1)
		ft_exit("no sprite texture path\n", window);
}

static void	parse_line(t_window *window, char *line, t_list *map_list, int i)
{
	while (ft_iswhitespace(line[i]))
		i++;
	if (line[i] == '\0' && window->map->map_started == TRUE)
		ft_exit("empty line inside or after map\n", window);
	else if (line[i] == '\0' && window->map->map_started == FALSE)
		return ;
	else if (line[i] == 'R')
		parse_resolution(window, line + i + 1);
	else if (line[i] == 'F' || line[i] == 'C')
		parse_color(window, line + i);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		parse_texture(window, window->textures->north, line + i + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		parse_texture(window, window->textures->south, line + i + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		parse_texture(window, window->textures->west, line + i + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		parse_texture(window, window->textures->east, line + i + 2);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		parse_texture(window, window->textures->sprite, line + i + 2);
	else if (line[i] == '1' || line[i] == '0')
		parse_map(window, line, map_list);
	else if ((line[i] && line[i] != '\0'))
		ft_exit("unknown identifier\n", window);
}

static void	handle_map(t_window *window, t_list	*map_list)
{
	t_list	*temp;

	if (ft_lstsize(map_list) == 1)
		ft_exit("no map provided\n", window);
	map_list = map_list->next;
	window->map->max_row = ft_lstsize(map_list);
	save_map(window, window->map, map_list);
	check_start_pos(window);
	window->map->arr_malloc = 1;
	// printf("row:%d col: %d\n", window->map->max_row, window->map->max_col);
	check_borders(window, window->map->max_row, window->map->max_col);
	check_map(window, window->map->row_pos, window->map->col_pos);
	restore_map(window->map);
	while (map_list)
	{
		temp = map_list->next;
		free(map_list);
		map_list = temp;
	}
}

void	parse_map(t_window *window, char *line, t_list *map_list)
{
	int		i;
	t_list	*new;

	window->map->map_started = TRUE;
	i = 0;
	while (line[i])
	{
		if (ft_strchr("012NSEW ", line[i]) == NULL)
			ft_exit("invalid char inside map\n", window);
		i++;
	}
	if (window->map->max_col < ft_strlen(line))
		window->map->max_col = ft_strlen(line);
	new = ft_lstnew(ft_strdup(line));
	if (!new)
		ft_exit("ft_lstnew failed\n", window);
	ft_lstadd_back(&map_list, new);
}

int	parse(char *file_name, t_window *window)
{
	int		ret_val;
	int		fd;
	char	*line;
	t_list	*map_list;

	fd = open(file_name, O_RDONLY);
	ret_val = 1;
	line = NULL;
	while (ret_val > 0)
	{
		ret_val = get_next_line(fd, &line);
		if (ret_val == -1)
			ft_exit("get next line failed\n", window);
		else if (ret_val > 0)
			parse_line(window, line, map_list, 0);
		free(line);
	}
	parse_check(window);
	handle_map(window, map_list);
	close(fd);
	return (0);
}
