/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_color_size.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 16:09:36 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/02/21 21:23:56 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		parse_resolution(t_window *window, char *line)
{
	//is there a max window size? 2560 * 1440/1400?
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
