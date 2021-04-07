/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 15:37:02 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/07 22:49:32 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite_info(t_window *window)
{
	if (!(window->s_info = malloc(sizeof(t_sprite_info))))
		ft_exit("Malloc failed\n");
	ft_bzero(window->s_info, sizeof(t_sprite_info));
}

//implement bubble sort
// void	sort_sprites()
// {

// }

//create sprite? save sprites in a linked list? and save its position in the map?
// void	handle_sprite(t_window *window, t_ray *ray, t_list *s_list)
// {
// 	// t_list		*new;
// 	// t_sprite	*sprite;

// 	// sprite = (t_sprite*)malloc(sizeof(sprite));
// 	// if (!sprite)
// 	// 	exit_w_message("malloc failed\n", 1, window);
// 	// sprite->x = ray->map_x;
// 	// sprite->y = ray->map_y;
// 	// new = ft_lstnew(sprite);
// 	// if (!new)
// 	// 	exit_w_message("ft_lstnew failed\n", 1, window);
// 	// ft_lstadd_back(&s_list, new);
// }

void	draw_sprites(t_window *window, t_ray *ray)
{
	//create s somewhere and link it to window and access it here;
	t_sprite_info	*s;
	t_player		*p;
	int				color;
	int				i;
	t_sprite		sprite[1]; //this will be created in handle_sprite

	init_sprite_info(window);
	sprite[0].x = 26;
	sprite[0].y = 8;
	printf("y:%f x:%f\n", sprite[0].y, sprite[0].x);
	s = window->s_info;
	p = window->player;
	printf("p:%f\n", p->pos_x);
	//sort the sprites
	//draw sprites one by one with a loop that goes through the linked list
	s->num_sprites = 1;
	i = 0;
	while(i < s->num_sprites)
	{
		//translate sprite position to relative to camera
		s->sprite_x = sprite[i].x - (p->pos_x - 0.5);
		s->sprite_y = sprite[i].y - (p->pos_y - 0.5);
		printf("s_x:%f - s_y:%f\n", s->sprite_x, s->sprite_y);
		//further calculations
			//intDev, transform_x, transform_y, sprite_screen_x, sprite_height
			s->inv_det = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);
			s->transform_x = s->inv_det * (p->dir_y * s->sprite_x - p->dir_x * s->sprite_y);
			s->transform_y = s->inv_det * (-p->plane_y * s->sprite_x + p->plane_x * s->sprite_y);
			s->sprite_screen_x = (int)(window->width / 2) * (1 + s->transform_x / s->transform_y); //not sure about window->w
			//fabs or abs?
			s->sprite_height = abs((int)(window->height/ s->transform_y));
			printf("s_h:%d \n", s->sprite_height);
			//calculate lowest and highest pixel to fill in current stripe
			s->draw_start_y = -s->sprite_height / 2 + window->height / 2;
			if (s->draw_start_y < 0)
				s->draw_start_y = 0;
			s->draw_end_y = s->sprite_height / 2 + window->height / 2;
			if (s->draw_end_y >= window->height)
				s->draw_end_y = window->height - 1;
			printf("s_d_s_y:%d - s_d_e_y:%d\n", s->draw_start_y, s->draw_end_y);
			s->sprite_width = abs((int)(window->height / s->transform_y));
			printf("s_w:%d \n", s->sprite_width);
			s->draw_start_x = -s->sprite_width / 2 + s->sprite_screen_x;
			if (s->draw_start_x < 0)
				s->draw_start_x = 0;
			s->draw_end_x = s->sprite_width / 2 + s->sprite_screen_x;
			if (s->draw_end_x >= window->width)
				s->draw_end_x = window->width - 1;
			printf("s_d_s_x:%d - s_d_e_x:%d\n", s->draw_start_x, s->draw_end_x);
		//loop through every vertical stripe of the sprite on screen
		s->stripe = s->draw_start_x;
		printf("s_stripe:%d \n", s->stripe);
		while (s->stripe < s->draw_end_x)
		{
			//changed the cals for the next line! (the reason?)
			s->tex_x = (int)(256 * (s->stripe - (-s->sprite_width / 2 + s-> sprite_screen_x)) * window->textures->sprite->width / s->sprite_width) / window->textures->sprite->line_length;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(s->transform_y > 0 && s->stripe > 0 && s->stripe < window->width && s->transform_y < ray->z_buffer[s->stripe]) //what for? - the loop - indentantion?
			{
				s->y = s->draw_start_y;
				while (s->y < s->draw_end_y) //for every pixel of the current stripe
				{
					s->d = (s->y) * 256 - window->height * 128 + s->sprite_height * 128; //256 and 128 factors to avoid floats
					//change 64 here: it's actually tex_height but there is a problem with it
					s->tex_y = ((s->d * 64) / s->sprite_height) / 256;
					color = my_mlx_pixel_get(window->textures->sprite, s->tex_x, s->tex_y); // texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture

					// //paint pixel if it isn't black, black is the invisible color
					if ((color & 0x00FFFFFF) != 0)
					{
						// printf("color:%d \n", color);
						my_mlx_pixel_set(window->image, s->stripe, s->y, color); //not sure: buffer[y][stripe] = color;
					}
					s->y++;
				}
			}
			s->stripe++;
		}
		printf("s_stripe:%d \n", s->stripe);
		//check out stripe value?
		//pixels from string and black check
	}
	//free the linked list
}
