/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 12:47:23 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/28 03:26:08 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_input(int argc, char **argv, int *screenshot)
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
			*screenshot = 1;
	}
}

int	main(int argc, char **argv)
{
	t_window	window;
	int			screenshot;

	validate_input(argc, argv, &screenshot);
	init_window(&window);
	window.screenshot = screenshot;
	init_map(&window);
	window.map_malloc = 1;
	init_textures(&window);
	init_player(&window);
	window.player_malloc = 1;
	init_keys(&window);
	window.keys_malloc = 1;
	parse(argv[1], &window);
	init_image(&window);
	window.win = mlx_new_window(window.mlx, window.width,
			window.height, "cub3D");
	mlx_hook(window.win, EVENT_KEY_PRESS, 1L << 0, key_pressed, &window);
	mlx_hook(window.win, EVENT_KEY_RELEASE, 1L << 1, key_released, &window);
	mlx_hook(window.win, EVENT_EXIT, 1L << 17, exit_game, &window);
	mlx_loop_hook(window.mlx, handle_loop, &window);
	mlx_loop(window.mlx);
	return (0);
}
