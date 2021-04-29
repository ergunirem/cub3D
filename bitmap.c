/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/16 15:25:07 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/29 18:22:54 by icikrikc      ########   odam.nl         */
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

/*
File Header(14 bytes): FileType'BM'(2 bytes) + FileSize(4 bytes) +
Reserved(4 bytes) + Reserved(4 bytes) + PixelDataOffset(4 bytes)
*/

static void	set_file_header(t_bmp *bmp, t_image *img, t_window *win)
{
	int	i;

	i = 0;
	while (i < 14)
		bmp->file_header[i++] = (unsigned char)(0);
	bmp->file_size = 14 + 40 + (bmp->stride * img->height);
	bmp->file_header[0] = (unsigned char)('B');
	bmp->file_header[1] = (unsigned char)('M');
	bmp->file_header[2] = (unsigned char)(bmp->file_size);
	bmp->file_header[3] = (unsigned char)(bmp->file_size >> 8);
	bmp->file_header[4] = (unsigned char)(bmp->file_size >> 16);
	bmp->file_header[5] = (unsigned char)(bmp->file_size >> 24);
	bmp->file_header[10] = (unsigned char)(14 + 40);
	bmp->check = write(bmp->fd, bmp->file_header, 14);
	if (bmp->check < 0)
		ft_exit("write failed in set_file_header\n", win);
}

/* InfoHeader(40 bytes): HeaderSize = 40(4 bytes) +
ImageWidth(4 Bytes) + ImageHeight(4 Bytes)
+ Planes=1(2 bytes)
+ BitsPerPixel=0(2 Bytes) + Compression=0(4 Bytes)
+ ImageSize=0(4 bytes) + XpixelsPerMeter=0(4 Bytes)
+ YpixelsPerMeter=0(4 Bytes) + TotalColors=0(4 Bytes)
+ ImportantColors=0(4 Bytes)
*/

static void	set_info_header(t_bmp *bmp, t_image *img, t_window *win)
{
	int	i;

	i = 0;
	while (i < 40)
		bmp->info_header[i++] = 0;
	bmp->info_header[0] = (unsigned char)(40);
	bmp->info_header[4] = (unsigned char)(img->width);
	bmp->info_header[5] = (unsigned char)(img->width >> 8);
	bmp->info_header[6] = (unsigned char)(img->width >> 16);
	bmp->info_header[7] = (unsigned char)(img->width >> 24);
	bmp->info_header[8] = (unsigned char)(-img->height);
	bmp->info_header[9] = (unsigned char)(-img->height >> 8);
	bmp->info_header[10] = (unsigned char)(-img->height >> 16);
	bmp->info_header[11] = (unsigned char)(-img->height >> 24);
	bmp->info_header[12] = (unsigned char)(1);
	bmp->info_header[14] = (unsigned char)(8 * 4);
	bmp->check = write(bmp->fd, bmp->info_header, 40);
	if (bmp->check < 0)
		ft_exit("write failed in set_info_header\n", win);
}

void	create_bitmap(t_window *window, t_image *img, int y)
{
	t_bmp	bmp;

	bmp.fd = open("cub3d.bmp", O_CREAT | O_WRONLY, S_IRWXU);
	if (bmp.fd < 0)
		ft_exit("open failed in create_bitmap\n", window);
	bmp.width_bytes = img->width * img->bits_per_pixel / 8;
	bmp.pad_size = (4 - (bmp.width_bytes) % 4) % 4;
	bmp.stride = bmp.width_bytes + bmp.pad_size;
	set_file_header(&bmp, img, window);
	set_info_header(&bmp, img, window);
	set_pad(&bmp);
	bmp.img = (unsigned char *)img->addr;
	y = 0;
	while (y < img->height)
	{
		bmp.check = write(bmp.fd, bmp.img + (y * img->line_length),
				img->width * 4);
		if (bmp.check < 0)
			ft_exit("write failed in create_bitmap\n", window);
		bmp.check = write(bmp.fd, bmp.pad, bmp.pad_size);
		if (bmp.check < 0)
			ft_exit("write failed in create_bitmap\n", window);
		y++;
	}
	close(bmp.fd);
}
