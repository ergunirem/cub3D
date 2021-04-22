/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 12:47:23 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/22 16:11:52 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_input(int argc, char **argv, t_window *window)
{
	int	len;

	if (argc == 1)
		ft_exit_basic("No argument provided\n");
	if (argc > 3)
		ft_exit_basic("More than 2 arguments\n");
	if (argv[1])
	{
		len = ft_strlen(argv[1]);
		if (len >= 4 && (argv[1][len - 4] != '.' || argv[1][len - 3] != 'c'
				|| argv[1][len - 2] != 'u' || argv[1][len - 1] != 'b'))
			ft_exit_basic(".cub extension needed!\n");
		else if (len < 4)
			ft_exit_basic(".cub extension needed!\n");
	}
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7))
			ft_exit_basic("Invalid screenshot argument\n");
		else
			window->screenshot = 1;
	}
}

int	main(int argc, char **argv)
{
	t_window	*window;

	validate_input(argc, argv, window);
	window = init_window();
	init_map(window);
	init_textures(window);
	init_player(window);
	init_keys(window);
	parse(argv[1], window);
	init_image(window);
	init_sprite_info(window);
	window->win = mlx_new_window(window->mlx, window->width, window->height, "cub3D");
	mlx_hook(window->win, EVENT_KEY_PRESS, 1L << 0, key_pressed, window);
	mlx_hook(window->win, EVENT_KEY_RELEASE, 1L << 1, key_released, window);
	mlx_hook(window->win, EVENT_EXIT, 1L << 17, exit_game, window);
	mlx_loop_hook(window->mlx, handle_loop, window);
	mlx_loop(window->mlx);
	return (0);
}
