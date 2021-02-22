/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 10:20:45 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/02/21 22:26:02 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parse_texture(t_window *window, t_image *img, char *line)
{
	char	*path;
	int		len;
	int		fd;
	int		img_width;
	int		img_height; //can I have them inside img struct?

	path = ft_strtrim(line, " ");
	if (path == NULL)
		exit_w_message("Error: ft_strtrim failed\n", 1, window);
	len = ft_strlen(path);
	if (len > 4 && (path[len - 4] != '.' || path[len - 3] != 'x' || path[len - 2] != 'p' || path[len - 1] != 'm'))
		exit_w_message("Error: .xpm extension needed\n", 1, window);
	else if (len < 4)
		exit_w_message("Error: Invalid texture path\n", 1, window);
	fd = open(path, O_RDONLY);
	printf("%s\n", path);
	if (fd < 0)
		exit_w_message("Error: opening xpm file failed\n", 1, window);
	img->img = mlx_xpm_file_to_image(window->mlx, path, &img_width, &img_height);
	//check img == NULL or width&height? == 64*64
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
									&img->endian);
	printf("%s, %d, %d\n", path, img_width, img_height);
	free(path);
	close(fd);
}

// static void parse_check(t_window *window)
// {
// 	if (window->width <= 0 || window->height <= 0)
// 		exit_w_message("Invalid resolution\n", 1, window);
// 	if(window->map->floor_color < 0 || window->map->ceiling_color < 0)
// 		exit_w_message("Invalid floor/ceiling color\n", 1, window);
// }

static void	get_info(t_window *window, char *line)
{
	while(ft_iswhitespace(*line))
		line++;
	// if (*line == '\0')
	// 	return (0);//if it's en empty line get out of the func to be faster?
	//Can it contain other chars (except R, F, C, S, NO etc.) = my logic FAILS
	if (*line == 'R')
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
}

int			parse(char *file_name, t_window *window)
{
	int ret_val;
	int fd;
	char *line;

	fd = open(file_name, O_RDONLY);
	ret_val = 1;
	line = NULL;
	while (ret_val > 0)
	{
		ret_val = get_next_line(fd, &line);
		if (ret_val == -1)
			exit (-1); //handles both fd&malloc errors
		// printf("%s\n", line);
		get_info(window, line);
		free(line);
	}
	close(fd);
	// free(line); //double-free error? but what about the last line ret val is 0?
	return (0);
}
