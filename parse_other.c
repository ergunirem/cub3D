/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_other.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 16:09:36 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/29 18:50:09 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_texture(t_window *win, t_image *img, char *line)
{
	char	*path;
	int		x;

	if (win->map->map_started == TRUE)
		ft_exit("map is not the last info\n", win);
	path = ft_strtrim(line, " ");
	if (path == NULL)
		ft_exit("ft_strtrim failed\n", win);
	x = ft_strlen(path);
	if (x > 4 && (path[x - 4] != '.' || path[x - 3] != 'x'
			|| path[x - 2] != 'p' || path[x - 1] != 'm'))
		ft_exit(".xpm extension needed\n", win);
	else if (x < 4)
		ft_exit("Invalid texture path\n", win);
	x = open(path, O_RDONLY);
	if (x < 0)
		ft_exit("opening xpm file failed\n", win);
	img->img = mlx_xpm_file_to_image(win->mlx, path, &img->width, &img->height);
	if (!img->img)
		ft_exit("xpm_to_image failed\n", win);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	win->textures->tex_num = win->textures->tex_num + 1;
	free(path);
	close(x);
}

void	parse_resolution(t_window *window, char *line)
{
	int		screen_x;
	int		screen_y;
	void	*mlx_ptr;

	if (window->map->map_started == TRUE)
		ft_exit("map is not the last info\n", window);
	while (ft_iswhitespace(*line))
		line++;
	mlx_get_screen_size(mlx_ptr, &screen_x, &screen_y);
	window->width = ft_atoi(line);
	if (window->width > screen_x && screen_x > 0)
		window->width = screen_x;
	while (ft_isdigit(*line))
		line++;
	window->height = ft_atoi(line);
	if (window->height > screen_y && screen_y > 0)
		window->height = screen_y;
	if (line)
		line++;
	while (ft_isdigit(*line))
		line++;
	while (ft_iswhitespace(*line))
		line++;
	if (*line != '\0')
		ft_exit("Resolution info is incorrect\n", window);
}

static int	calculate_color_from_rgb(int r, int g, int b)
{
	int	rgb;

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);
}

static	int	get_color(char *line, int *index, t_window *window)
{
	int	color;

	color = ft_atoi(line + *index);
	if (color < 0 || color > 255)
		ft_exit("invalid rgb values\n", window);
	while (ft_isdigit(line[*index]))
		(*index)++;
	(*index)++;
	return (color);
}

void	parse_color(t_window *window, char *line)
{
	char	info;
	int		r;
	int		g;
	int		b;
	int		index;

	if (window->map->map_started == TRUE)
		ft_exit("map is not the last info\n", window);
	info = *line;
	line++;
	while (ft_iswhitespace(*line))
		line++;
	index = 0;
	r = get_color(line, &index, window);
	g = get_color(line, &index, window);
	b = get_color(line, &index, window);
	if (info == 'F')
		window->map->floor_color = calculate_color_from_rgb(r, g, b);
	else if (info == 'C')
		window->map->ceiling_color = calculate_color_from_rgb(r, g, b);
}
