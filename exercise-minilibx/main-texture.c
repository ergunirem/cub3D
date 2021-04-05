
#include "../minilibx_opengl/mlx.h"
#include "../utils/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct  s_image {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	int			width;
	int			height;
}               t_image;

int				mlx_pixel_get(t_image *img, int x, int y)
{
	int		color;
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void			mlx_pixel_set(t_image *img, int x, int y, int color)
{
	char		*dst;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int     main(void)
{
    void    *mlx;
	t_image  data;
	t_image  *image;
    char    *relative_path = "../textures/bluestone.xpm";
    int     img_width;
    int     img_height;
	void    *win;
	int color;

    mlx = mlx_init();
	win = mlx_new_window(mlx, 640, 480, "Hello world!");
	if (!(image = malloc(sizeof(t_image))))
		return (-1);
	ft_bzero(image, sizeof(t_image));
	if (!(image->img = mlx_new_image(mlx, 640, 640)))
		return (-1);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length,
                                 &image->endian);


    data.img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	printf("h: %d\n", img_height);
	printf("w: %d\n", img_width);

	int x = 0;
	while ( x < 63)
	{
		int y = 0;
		while (y < 63)
		{
			color = mlx_pixel_get(&data, x, y);
			printf("c: %d\n", color);
			mlx_pixel_set(image, x, y, color);
			y++;
		}
		x++;
	}

	mlx_put_image_to_window(mlx, win, image->img, 0, 0);
	mlx_loop(mlx);
}
