/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/16 15:25:07 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/20 02:27:20 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pad(t_bmp *bmp)
{
	int	i;

	i = 0;
	while (i < 3)
		bmp->pad[i++] = 0;
}

void	write_pixels(t_window *window, t_bmp	*bmp)
{
	int	i;
	int	j;
	int	x;
	int	y;

	j = -1;
	while (++j < window->height)
	{
		i = -1;
		while (++i < window->width)
		{
			x = i;
			y = window->height - 1 - j;
			bmp->color = window->image->addr[x + y * window->width];
			if (write(bmp->fd, &bmp->color, 3) < 0)
				ft_exit("write failed in set_file_header\n", window);
		}
		i = -1;
		while (++i < (4 - (window->width * 3) % 4) % 4)
		{
			if (write(bmp->fd, &bmp->pad, 1) < 0)
				ft_exit("write failed in set_file_header\n", window);
		}
	}
}

/*
InfoHeader(40 bytes): HeaderSize = 40(4 bytes) + ImageWidth(4 Bytes) + ImageHeight(4 Bytes) + Planes=1(2 bytes)
+ BitsPerPixel=0(2 Bytes) + Compression=0(4 Bytes) + ImageSize=0(4 bytes) + XpixelsPerMeter=0(4 Bytes)
+ YpixelsPerMeter=0(4 Bytes) + TotalColors=0(4 Bytes) + ImportantColors=0(4 Bytes)
*/

void	set_info_header(t_window *window, t_bmp	*bmp)
{
	int	i;

	i = 0;
	while (i < 40)
		bmp->info[i++] = 0;
	bmp->info[0] = 40;
	bmp->info[4] = (unsigned char)(window->width);
	bmp->info[5] = (unsigned char)(window->width >> 8);
	bmp->info[6] = (unsigned char)(window->width >> 16);
	bmp->info[7] = (unsigned char)(window->width >> 24);
	bmp->info[8] = (unsigned char)(window->height);
	bmp->info[9] = (unsigned char)(window->height >> 8);
	bmp->info[10] = (unsigned char)(window->height >> 16);
	bmp->info[11] = (unsigned char)(window->height >> 24);
	bmp->info[12] = 1;
	bmp->info[14] = 24;
	i = write(bmp->fd, bmp->info, 40);
	if (i < 0)
		ft_exit("write failed in set_file_header\n", window);
}

/*
File Header(14 bytes): FileType'BM'(2 bytes) + FileSize(4 bytes) +
Reserved(4 bytes) + Reserved(4 bytes) + PixelDataOffset(4 bytes)
*/

void	set_file_header(t_window *window, t_bmp	*bmp)
{
	int	i;

	i = 0;
	while (i < 14)
		bmp->header[i++] = 0;
	bmp->header[0] = 'B';
	bmp->header[1] = 'M';
	bmp->header[2] = (unsigned char)(bmp->size);
	bmp->header[3] = (unsigned char)(bmp->size >> 8);
	bmp->header[4] = (unsigned char)(bmp->size >> 16);
	bmp->header[5] = (unsigned char)(bmp->size >> 24);
	bmp->header[10] = 54; //?
	i = write(bmp->fd, bmp->header, 14);
	if (i < 0)
		ft_exit("write failed in set_file_header\n", window);
}

void	create_bitmap(t_window *window)
{
	int		img_size;
	t_bmp	*bmp;

	bmp->fd = open("cub3D.bmp", O_CREAT | O_WRONLY, S_IRWXU);
	if (bmp->fd == -1)
		ft_exit("open failed in create_bitmap\n", window);
	img_size = 3 * window->height * window->width;
	bmp->size = 54 + img_size;
	bmp->img = (char*)malloc((sizeof(char) * img_size));
	if (!bmp->img)
		ft_exit("malloc failed in create_bitmap\n", window);
	ft_bzero(bmp->img, img_size);
	set_file_header(window, bmp);
	set_info_header(window, bmp);
	set_pad(bmp);
	write_pixels(window, bmp);
	free(bmp->img);
	close(bmp->fd);
}
