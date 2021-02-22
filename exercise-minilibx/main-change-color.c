#include "cub3d.h"
#include <stdio.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	int 		color;
}               t_data;

typedef struct  s_window {
	void    	*mlx;
    void    	*win;
    t_data		*image;
}               t_window;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int	change_color(int keycode, t_window *window)
{
	if (keycode == 13)
		window->image->color = 0x00FFFF00;
	if (keycode == 0)
		window->image->color = 0x000000FF;
	if (keycode == 1)
		window->image->color = 0x00FF0000;
	if (keycode == 2)
		window->image->color = 0x0000FF00;

	return (0);
}

int color_screen(t_window *window, t_data *data)
{
	int x = 0;
	while (x < 640)
	{
		int y = 0;
		while (y < 480)
		{
			my_mlx_pixel_put(data, x, y, data->color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(window->mlx, window->win, window->image->img, 0, 0);
	return (0);
}

int     render_next_frame(t_window *window)
{
	color_screen(window, window->image);
	return (0);
}

int             main(void)
{
	t_window window;
	t_data  data;

    window.mlx = mlx_init();
    window.win = mlx_new_window(window.mlx, 640, 480, "Hello world!");
	data.img = mlx_new_image(window.mlx, 640, 480);
	window.image = &data;
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
                                 &data.endian);
	mlx_hook(window.win, 2, 1L<<0, change_color, &window);
	mlx_loop_hook(window.mlx, render_next_frame, &window);
    mlx_loop(window.mlx);
	return (0);
}
