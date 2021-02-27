/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/10 14:36:42 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/02/26 21:15:25 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx_opengl/mlx.h"
# include "utils/gnl/get_next_line.h"
# include "utils/libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

# define EVENT_KEY_PRESS		2
# define EVENT_KEY_RELEASE		3
# define EVENT_MOUSE_PRESS		4
# define EVENT_MOUSE_RELEASE	5
# define EVENT_MOUSE_MOVE		6
# define EVENT_EXIT				17

# define TRUE					0 //problem with other macros?
# define FALSE					1


typedef struct  s_image {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_image;

typedef struct  s_map {
	int			map_started;
	int			floor_color;
	int			ceiling_color;
	char		**map_array;
	int			max_row;
	int			max_col;
	int			row_pos;
	int			col_pos;
}				t_map;

typedef struct  s_tex {
	t_image		*north;
	t_image		*south;
	t_image		*east;
	t_image		*west;
	t_image		*sprite;
}				t_tex;

typedef struct  s_window {
	void		*mlx;
	void		*win;
	int			height;
	int			width;
	int			screenshot;
	t_map		*map;
	t_image		*image;
	t_tex 		*textures;
}				t_window;

//not proper funcs
// int key_pressed(int keycode, void *param);
// int key_released(int keycode, void *param);
// int exit(void *param);

//proper funcs
int		parse(char *file_name, t_window *window);
void	parse_texture(t_window *window, t_image *img, char *line);
void	parse_resolution(t_window *window, char *line);
void	parse_color(t_window *window, char *line);
void	parse_map(t_window *window, char *line, t_list *map_list);
void	save_map(t_window *window, t_map *map, t_list *map_list);
void	check_start_pos(t_window *window);
void	check_map(t_window *window, int row, int col);

void	exit_w_message(char *msg, int window_open, t_window *window);
void	ft_exit(char *msg);
void	init_map(t_window *window, t_map *map);
void	init_textures(t_window *window, t_tex *textures);

#endif