#include "cub3d.h"

int key_pressed(int keycode, void *param)
{

}

int key_released(int keycode, void *param)
{

}

int exit_game(void *param)
{

}

int	handle_loop(void *param)
{
	t_window *window;

	window = (t_window *)param;
	draw(window);
	return (0);
}
