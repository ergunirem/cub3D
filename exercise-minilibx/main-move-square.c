#include "cub3d.h"
#include <stdio.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	int 		color;
	int			x;
	int         y;
	int			x_offset;
	int         y_offset;
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

int draw_square(t_data *data, t_window *window)
{
	int x = 0;
	while (x < 640)
	{
		int y = 0;
		while (y < 480)
		{
			my_mlx_pixel_put(data, x, y, 0x00000000);
			y++;
		}
		x++;
	}
	// mlx_put_image_to_window(window->mlx, window->win, window->image->img, 0, 0);
	int i = data->x_offset;
	while (i < data->x_offset+100)
	{
		my_mlx_pixel_put(data, data->x, i, 0x00FF0000);
		i++;
	}
	i = data->x_offset;
	while (i < data->x_offset+100)
	{
		my_mlx_pixel_put(data, data->x+100, i, 0x00FFFF00);
		i++;
	}
	i = data->y_offset;
	while (i < data->y_offset+100)
	{
		my_mlx_pixel_put(data, i, data->y, 0x0000FF00);
		i++;
	}
	i = data->y_offset;
	while (i < data->y_offset+100)
	{
		my_mlx_pixel_put(data, i, data->y+100, 0x000000FF);
		i++;
	}
    mlx_put_image_to_window(window->mlx, window->win, window->image->img, 0, 0);
	return (0);
}

int	move(int keycode, t_window *window)
{
	if (keycode == 13)
	{
		window->image->x_offset = window->image->x_offset - 1;
		window->image->y = window->image->y - 1;
	}
	else if (keycode == 0)
	{
		window->image->x = window->image->x - 1;
		window->image->y_offset = window->image->y_offset - 1;
	}
	else if (keycode == 1)
	{
		window->image->x_offset = window->image->x_offset + 1;
		window->image->y = window->image->y + 1;
	}
	else if (keycode == 2)
	{
		window->image->x = window->image->x + 1;
		window->image->y_offset = window->image->y_offset + 1;
	}
	return (0);
}

int     render_next_frame(t_window *window)
{
	draw_square(window->image, window);
	return (0);
}

int     main(void)
{
	t_window window;
	t_data  data;

    window.mlx = mlx_init();
    window.win = mlx_new_window(window.mlx, 640, 480, "Hello world!");
	data.img = mlx_new_image(window.mlx, 640, 480);
	window.image = &data;
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
                                 &data.endian);
	mlx_hook(window.win, 2, 1L<<0, move, &window);
	mlx_loop_hook(window.mlx, render_next_frame, &window);
    mlx_loop(window.mlx);
}

