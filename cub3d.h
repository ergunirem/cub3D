/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/10 14:36:42 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/30 00:22:37 by icikrikc      ########   odam.nl         */
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
# include <time.h>

# define EVENT_KEY_PRESS		2
# define EVENT_KEY_RELEASE		3
# define EVENT_MOUSE_PRESS		4
# define EVENT_MOUSE_RELEASE	5
# define EVENT_MOUSE_MOVE		6
# define EVENT_EXIT				17

# define TRUE					0
# define FALSE					1

typedef struct s_bmp
{
	int				fd;
	int				file_size;
	int				width_bytes;
	int				pad_size;
	int				stride;
	int				check;
	unsigned char	*img;
	unsigned char	file_header[14];
	unsigned char	info_header[40];
	unsigned char	pad[3];
}					t_bmp;

typedef struct s_sprite_info
{
	int			s_screen_x;
	int			s_height;
	int			s_width;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_end_x;
	int			tex_x;
	int			tex_y;
	int			stripe;
	int			d;
	int			y;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		trans_x;
	double		trans_y;
}				t_sprite_info;

typedef struct s_keys
{
	int			forward;
	int			backward;
	int			left;
	int			right;
	int			look_left;
	int			look_right;
	int			close;
}				t_keys;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		move_speed;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		rotate_speed;
	double		cam_height;
	int			health;
}				t_player;

typedef struct s_ray
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
}				t_ray;

typedef struct s_image {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_image;

typedef struct s_map {
	int			map_started;
	int			floor_color;
	int			ceiling_color;
	char		**map_array;
	int			max_row;
	int			max_col;
	int			row_pos;
	int			col_pos;
	int			arr_malloc;
}				t_map;

typedef struct s_tex {
	t_image		tex[5];
	int			tex_num;
	int			tex_x;
	int			tex_y;
	int			width;
	int			height;
	double		wall_x;
	double		tex_pos;
	double		step;
}				t_tex;

typedef struct s_window {
	void		*mlx;
	void		*win;
	int			height;
	int			width;
	int			screenshot;
	double		**spr;
	int			spr_num;
	t_map		*map;
	int			map_malloc;
	t_image		*image;
	int			image_malloc;
	t_tex		*textures;
	t_player	*player;
	t_keys		*keys;
	int			keys_malloc;
}				t_window;

//event funcs
int			key_pressed(int keycode, t_window *window);
int			key_released(int keycode, t_window *window);
int			exit_game(t_window *window);
int			handle_loop(void *param);
//pixel funcs
int			my_mlx_pixel_get(t_image *img, int x, int y);
void		my_mlx_pixel_set(t_image *img, int x, int y, int color);
void		color_vertical_line(t_window *window, int draw_start,
				int draw_end, int x_ray_pix);
//ray-casting
void		draw(t_window *window);
void		cast_ray(t_window *window, t_ray *ray);
void		init_ray(t_ray *ray, t_player *player, t_window *window);
void		next_step(t_ray *ray, t_player *player);
void		get_wall_side(t_ray *ray);
void		get_distance(t_ray *ray, t_player *player, t_window *window);
void		set_start_pos(t_window *window, char pos, int j, int i);
void		set_camera(t_window *win, double dir_x, double plane_x,
				double plane_y);
t_image		*designate_tex(t_ray *ray, t_window *window, double wall_x);
void		apply_textures(t_ray *ray, t_window *window);
void		draw_sprites(t_window *window, t_ray *ray);
void		get_sprites(t_window *window);
//hook funcs
void		move_forward(t_window *window);
void		move_backward(t_window *window);
void		move_left(t_window *window);
void		move_right(t_window *window);
void		look_left(t_window *window);
void		look_right(t_window *window);
//parse funcs
int			parse(char *file_name, t_window *window);
void		parse_texture(t_window *window, t_image *img, char *line);
void		parse_resolution(t_window *window, char *line);
void		parse_color(t_window *window, char *line);
void		parse_map(t_window *window, char *line, t_list *map_list);
void		save_map(t_window *window, t_map *map, t_list *map_list, int i);
void		check_start_pos(t_window *window);
void		check_map(t_window *window, int row, int col);
void		check_borders(t_window *window);
void		check_bottom(t_window *window);
void		check_top(t_window *window);
void		restore_map(t_map *map);
//exit funcs
void		ft_exit(char *msg, t_window *window);
void		ft_exit_basic(char *msg);
//init funcs
void		init_map(t_window *window);
t_tex		init_textures(t_window *window);
t_player	init_player(t_window *window);
void		init_keys(t_window *window);
void		init_image(t_window *window);
//bitmap func
void		create_bitmap(t_window *window, t_image *img, int y);
#endif
