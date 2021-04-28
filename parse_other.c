/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_other.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 16:09:36 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/28 17:24:11 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*can I have them inside img struct?
//check img == NULL or width&height? == 64*64
//printf("%s, %d, %d\n", path, img_width, img_height);
*/

void	parse_texture(t_window *window, t_image *img, char *line)
{
	char	*path;
	int		len;
	int		fd;

	if (window->map->map_started == TRUE)
		ft_exit("map is not the last info\n", window);
	path = ft_strtrim(line, " ");
	if (path == NULL)
		ft_exit("ft_strtrim failed\n", window);
	len = ft_strlen(path);
	if (len > 4 && (path[len - 4] != '.' || path[len - 3] != 'x'
			|| path[len - 2] != 'p' || path[len - 1] != 'm'))
		ft_exit(".xpm extension needed\n", window);
	else if (len < 4)
		ft_exit("Invalid texture path\n", window);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_exit("opening xpm file failed\n", window);
	img->img = mlx_xpm_file_to_image(window->mlx, path, &img->width,
			&img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	window->textures->tex_num = window->textures->tex_num + 1;
	free(path);
	close(fd);
}

/*printf("width:%d\n", window->width);
//printf("height:%d\n", window->height);*/

void	parse_resolution(t_window *window, char *line)
{
	if (window->map->map_started == TRUE)
		ft_exit("map is not the last info\n", window);
	while (ft_iswhitespace(*line))
		line++;
	window->width = ft_atoi(line);
	if (window->width > 2560)
		window->width = 2560;
	while (ft_isdigit(*line))
		line++;
	window->height = ft_atoi(line);
	if (window->height > 1440)
		window->height = 1440;
	if (line)
		line++;
	while (ft_isdigit(*line))
		line++;
	while (ft_iswhitespace(*line))
		line++;
	if (*line != '\0')
		ft_exit("Resolution info is incorrect\n", window);
}

/*printf("color:%d\n", rgb); */

static int	calculate_color_from_rgb(int r, int g, int b)
{
	int	rgb;

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);
}

/*will there be only a comma? any spaces? after each color no */

static	int	get_color(char *line, int *index)
{
	int	color;

	color = ft_atoi(line + *index);
	if (color < 0 || color > 255)
		exit(0); //change
	while (ft_isdigit(line[*index]))
		(*index)++;
	(*index)++;
	return (color);
}

/* printf("%d | %d | %d \n", r, g, b); */

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
	r = get_color(line, &index);
	g = get_color(line, &index);
	b = get_color(line, &index);
	if (info == 'F')
		window->map->floor_color = calculate_color_from_rgb(r, g, b);
	else if (info == 'C')
		window->map->ceiling_color = calculate_color_from_rgb(r, g, b);
}
