/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 12:47:23 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/02/27 07:56:22 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
// {
//     char    *dst;

//     dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//     *(unsigned int*)dst = color;
// }

void	validate_input(int argc, char **argv, t_window *window)
{
	int	len;

	if (argc == 1)
		exit_w_message("No argument provided\n", 1, window);
	if (argc > 3)
		exit_w_message("More than 2 arguments\n", 1, window);
	if (argv[1])
	{
		len = ft_strlen(argv[1]);
		if (len >= 4 && (argv[1][len - 4] != '.' || argv[1][len - 3] != 'c'
			|| argv[1][len - 2] != 'u' || argv[1][len - 1] != 'b'))
			exit_w_message(".cub extension needed!\n", 1, window);
		else if (len < 4)
			exit_w_message(".cub extension needed!\n", 1, window);
	}
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7))
			exit_w_message("Invalid screenshot argument\n", 1, window);
		else
			window->screenshot = 1;
	}
}

int	main(int argc, char **argv)
{
	t_window 	window;
	t_map		map;
	t_tex		textures;
	t_image		north;
	t_image		south;
	t_image		east;
	t_image		west;
	t_image		sprite;

	validate_input(argc, argv, &window);
	init_map(&window, &map);
	init_textures(&window, &textures);
	window.textures->north = &north;
	window.textures->south = &south;
	window.textures->east = &east;
	window.textures->west = &west;
	window.textures->sprite = &sprite;
	north.endian = -1;
	south.endian = -1;
	east.endian = -1;
	west.endian = -1;
	sprite.endian = -1;

	// window.mlx = mlx_init();
	// window.win = mlx_new_window(window.mlx, 640, 480, "cub3D");
	parse(argv[1], &window); //segfault after writing check_input?
	// mlx_loop(window.mlx);
	return (0);
}
