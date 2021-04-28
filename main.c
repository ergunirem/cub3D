/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 12:47:23 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/28 16:16:18 by icikrikc      ########   odam.nl         */
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

static void	init_window(t_window *new_window)
{
	ft_memset(new_window, 0, sizeof(t_window));
	new_window->mlx = mlx_init();
	if (!new_window->mlx)
		ft_exit("mlx_init failed\n", new_window);
	new_window->height = 0;
	new_window->width = 0;
	new_window->screenshot = 0;
}

int	main(int argc, char **argv)
{
	t_window	win;
	t_tex		textures;
	t_player	player;
	int			screenshot;

	validate_input(argc, argv, &screenshot);
	init_window(&win);
	win.screenshot = screenshot;
	init_map(&win);
	win.map_malloc = 1;
	textures = init_textures(&win);
	win.textures = &textures;
	player = init_player(&win);
	win.player = &player;
	init_keys(&win);
	win.keys_malloc = 1;
	parse(argv[1], &win);
	init_image(&win);
	win.win = mlx_new_window(win.mlx, win.width, win.height, "cub3D");
	mlx_hook(win.win, EVENT_KEY_PRESS, 1L << 0, key_pressed, &win);
	mlx_hook(win.win, EVENT_KEY_RELEASE, 1L << 1, key_released, &win);
	mlx_hook(win.win, EVENT_EXIT, 1L << 17, exit_game, &win);
	mlx_loop_hook(win.mlx, handle_loop, &win);
	mlx_loop(win.mlx);
	return (0);
}
