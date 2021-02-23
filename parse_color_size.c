/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_color_size.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 16:09:36 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/02/23 17:30:35 by icikrikc      ########   odam.nl         */
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

	if (window->map->map_started == TRUE)
		exit_w_message("map is not the last info\n", 1, window);
	path = ft_strtrim(line, " ");
	if (path == NULL)
		exit_w_message("ft_strtrim failed\n", 1, window);
	len = ft_strlen(path);
	if (len > 4 && (path[len - 4] != '.' || path[len - 3] != 'x' || path[len - 2] != 'p' || path[len - 1] != 'm'))
		exit_w_message(".xpm extension needed\n", 1, window);
	else if (len < 4)
		exit_w_message("Invalid texture path\n", 1, window);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_w_message("opening xpm file failed\n", 1, window);
	img->img = mlx_xpm_file_to_image(window->mlx, path, &img_width, &img_height);
	//check img == NULL or width&height? == 64*64
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
									&img->endian);
	//printf("%s, %d, %d\n", path, img_width, img_height);
	free(path);
	close(fd);
}

void		parse_resolution(t_window *window, char *line)
{
	if (window->map->map_started == TRUE)
		exit_w_message("map is not the last info\n", 1, window);
	//is there a max window size? 2560 * 1440/1400? //resize?
	while (ft_iswhitespace(*line))
		line++;
	window->width = ft_atoi(line);
	// if (window->width > 2560)
	// 	window->width = 2560;
	//printf("width:%d\n", window->width);
	while (ft_isdigit(*line))
		line++;
	window->height = ft_atoi(line);
	// if (window->height > 1440)
	// 	window->height = 1440;
	//printf("height:%d\n", window->height);
}

static int	calculate_color_from_rgb(int r, int g, int b)
{
	int rgb;

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	// printf("color:%d\n", rgb);
	return (rgb);
}

static	int	get_color(char *line, int *index)
{
	int color;

	color = ft_atoi(line + *index);
	if (color < 0 || color > 255)
		exit (-1);
	while (ft_isdigit(line[*index]))
		(*index)++;
	(*index)++; 	//will there be only a comma? any spaces?
	return (color);
}

void		parse_color(t_window *window, char *line)
{
	char	info;
	int		r;
	int		g;
	int		b;
	int		index;

	if (window->map->map_started == TRUE)
		exit_w_message("map is not the last info\n", 1, window);
	info = *line;
	line++;
	while (ft_iswhitespace(*line))
		line++;
	index = 0;
	r = get_color(line, &index);
	g = get_color(line, &index);
	b = get_color(line, &index);
	//printf("%d | %d | %d \n", r, g, b);
	if (info == 'F')
		window->map->floor_color = calculate_color_from_rgb(r, g, b);
	else if (info == 'C')
		window->map->ceiling_color = calculate_color_from_rgb(r, g, b);
}
