
#include "cub3d.h"
#include <stdio.h>
typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

// int     main(void)
// {
//     void    *mlx;
// 	void    *win;
//     void    *img;
//     char    *relative_path = ".exercise-minilibx/bluestone.xpm";
//     int     img_width;
//     int     img_height;

//     mlx = mlx_init();
// 	win = mlx_new_window(mlx, 640, 480, "Hello world!");
//     img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
// 	mlx_put_image_to_window(mlx, win, img, 0, 0);
// 	return (0);
// }
int     main(void)
{
    void    *mlx;
    void    *img;
	t_data  data;
    char    *relative_path = "./bluestone.xpm";
    int     img_width;
    int     img_height;
	void    *win;

    mlx = mlx_init();
    data.img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
                                 &data.endian);
	win = mlx_new_window(mlx, 640, 480, "Hello world!");
	printf("h: %d\n", img_height);
	printf("w: %d\n", img_width);
	mlx_put_image_to_window(mlx, win, data.img, 0, 0);
	// printf("i: %d\n", img);
}
