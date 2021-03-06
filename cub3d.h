/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/10 14:36:42 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/03/07 22:43:26 by icikrikc      ########   odam.nl         */
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
# include <math.h>

# define EVENT_KEY_PRESS		2
# define EVENT_KEY_RELEASE		3
# define EVENT_MOUSE_PRESS		4
# define EVENT_MOUSE_RELEASE	5
# define EVENT_MOUSE_MOVE		6
# define EVENT_EXIT				17

# define TRUE					0 //problem with other macros?
# define FALSE					1

typedef struct	s_keys
{
	int			forward;
	int			backward;
	int			left;
	int			right;
	int			look_left;
	int			look_right;
	int			close;
}				t_keys;

typedef	struct			s_player
{
	double				pos_x;
	double				pos_y;
	double				move_speed;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				rotate_speed;
	double				cam_height;
	int					health;
}						t_player;

typedef struct	s_ray
{
	int			pix;
	int			map_x;
	int			map_y;
	double		cam_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		del_dist_x;
	double		del_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		*z_buffer;
} t_ray;

typedef struct  s_image {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	int			width;
	int			height;
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
	t_tex		*textures;
	t_player	*player;
	t_keys		*keys;
}				t_window;

//not proper funcs
int key_pressed(int keycode, t_window *window);
int key_released(int keycode, t_window *window);
int exit_game(t_window *window);
// int	handle_loop(t_window *window);
int	handle_loop(void *param);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);

//ray-casting
void	draw(t_window *window);
void	color_vertical_line(t_window *window, int color, int draw_start, int draw_end, int x_ray_pix);

//hook funcs
void	move_forward(t_window *window);
void	move_backward(t_window *window);
void	move_left(t_window *window);
void	move_right(t_window *window);
void	look_left(t_window *window);
void	look_right(t_window *window);


//proper funcs
int		parse(char *file_name, t_window *window);
void	parse_texture(t_window *window, t_image *img, char *line);
void	parse_resolution(t_window *window, char *line);
void	parse_color(t_window *window, char *line);
void	parse_map(t_window *window, char *line, t_list *map_list);
void	save_map(t_window *window, t_map *map, t_list *map_list);
void	check_start_pos(t_window *window);
void	check_map(t_window *window, int row, int col);
//
void	set_start_camera(t_window *window, double dir_x, double plane_x, double plane_y);
//
void	exit_w_message(char *msg, int window_open, t_window *window);
void	ft_exit(char *msg);
void	init_map(t_window *window);
void	init_textures(t_window *window);
void	init_player(t_window *window);
void	init_keys(t_window *window);
t_window	*init_window(void);
#endif
