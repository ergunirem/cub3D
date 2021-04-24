/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 11:33:06 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/24 18:35:37 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_keys(t_window *window)
{
	if (window->keys->forward == 1)
		move_forward(window);
	if (window->keys->backward == 1)
		move_backward(window);
	if (window->keys->left == 1)
		move_left(window);
	if (window->keys->right == 1)
		move_right(window);
	if (window->keys->look_left == 1)
		look_left(window);
	if (window->keys->look_right == 1)
		look_right(window);
	if (window->keys->close == 1)
		exit_game(window);
}

int	key_pressed(int keycode, t_window *window)
{
	if (keycode == 13)
		window->keys->forward = 1;
	else if (keycode == 1)
		window->keys->backward = 1;
	else if (keycode == 0)
		window->keys->left = 1;
	else if (keycode == 2)
		window->keys->right = 1;
	else if (keycode == 123)
		window->keys->look_left = 1;
	else if (keycode == 124)
		window->keys->look_right = 1;
	else if (keycode == 53)
		window->keys->close = 1;
	return (0);
}

int	key_released(int keycode, t_window *window)
{
	if (keycode == 13 && window->keys->forward == 1)
		window->keys->forward = 0;
	else if (keycode == 1 && window->keys->backward == 1)
		window->keys->backward = 0;
	else if (keycode == 0 && window->keys->left == 1)
		window->keys->left = 0;
	else if (keycode == 2 && window->keys->right == 1)
		window->keys->right = 0;
	else if (keycode == 123 && window->keys->look_left == 1)
		window->keys->look_left = 0;
	else if (keycode == 124 && window->keys->look_right == 1)
		window->keys->look_right = 0;
	return (0);
}

int	exit_game(t_window *window)
{
	ft_exit("esc: exited the game\n", window);
	return (0);
}

int	handle_loop(void *param)
{
	t_window *window;

	window = (t_window *)param;
	draw(window);
	check_keys(window);
	return (0);
}
