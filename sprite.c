/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 15:37:02 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/09 21:31:43 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//implement bubble sort
// void	sort_sprites()
// {
// }

/*
It projects each sprite, calculates the size it should have on screen.
First, translates sprite position to relative to camera. Then, calculates
lowest and highest pixel to fill in current stripe.
*/

void	calculate_projection(t_sprite_info *s, t_window *window, t_sprite *sprite)
{
	// t_sprite	sprite[3]; //this will be created in handle_sprite
	t_player	*p;

	p = window->player;
	// sprite[0].x = 26;
	// sprite[0].y = 8;
	// sprite[1].x = 14;
	// sprite[1].y = 3;
	// sprite[2].x = 18;
	// sprite[2].y = 2;
	// printf("x:%f - y:%f\n", sprite->x, sprite->y);
	s->sprite_x = sprite->x - (p->pos_x - 0.5);
	s->sprite_y = sprite->y - (p->pos_y - 0.5);
	s->inv_det = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);
	s->transform_x = s->inv_det * (p->dir_y * s->sprite_x - p->dir_x * s->sprite_y);
	s->transform_y = s->inv_det * (-p->plane_y * s->sprite_x + p->plane_x * s->sprite_y);
	s->sprite_screen_x = (int)(window->width / 2) * (1 + s->transform_x / s->transform_y);
	s->sprite_height = abs((int)(window->height / s->transform_y));
	s->draw_start_y = -s->sprite_height / 2 + window->height / 2;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->sprite_height / 2 + window->height / 2;
	if (s->draw_end_y >= window->height)
		s->draw_end_y = window->height - 1;
	s->sprite_width = abs((int)(window->height / s->transform_y));
	s->draw_start_x = -s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_end_x >= window->width)
		s->draw_end_x = window->width - 1;
}

/*
It loops through every vertical stripe of the sprite on screen,
and if: it's in front of camera plane so you don't see things behind you &&
it's on the screen (left) && it's on the screen (right) &&
ZBuffer, with perpendicular distance, then it loops through every pixel of the stripe
gets the color for each pixel and paints it to the window if not black.
*/

void	draw_vertical_stripe(t_sprite_info *s,  t_ray *ray, t_window *window)
{
	int	color;

	s->stripe = s->draw_start_x;
	while (s->stripe < s->draw_end_x)
	{
		s->tex_x = (int)(256 * (s->stripe - (-s->sprite_width / 2 + s->sprite_screen_x)) * window->textures->sprite->width / s->sprite_width) / window->textures->sprite->line_length;
		if(s->transform_y > 0 && s->stripe > 0 && s->stripe < window->width && s->transform_y < ray->z_buffer[s->stripe])
		{
			s->y = s->draw_start_y;
			while (s->y < s->draw_end_y)
			{
				s->d = (s->y) * 256 - window->height * 128 + s->sprite_height * 128;
				s->tex_y = ((s->d * 64) / s->sprite_height) / 256; //change 64 here: it's actually tex_height but there is a problem with it
				color = my_mlx_pixel_get(window->textures->sprite, s->tex_x, s->tex_y);
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_set(window->image, s->stripe, s->y, color);
				s->y++;
			}
		}
		s->stripe++;
	}
}

/*
Draws sprites one by one with a loop that goes through the linked list
*/

void	draw_sprites(t_window *window, t_ray *ray)
{
	t_sprite_info	*s;
	t_sprite		*current_sprite;
	t_sprite		*s_list_tmp;
	t_player		*p;
	int				i;

	s = window->s_info;
	s_list_tmp = s->s_list;
	// sort_sprites(s);
	s->num_sprites = my_lstsize(s_list_tmp);
	printf("numS: %d\n", s->num_sprites);
	// i = 0;
	while(s_list_tmp->next != NULL)
	{
		if (s_list_tmp->next)
			current_sprite = s_list_tmp->next;
		// printf("-x:%f - y:%f\n", current_sprite->x, current_sprite->y);
		// printf("-x:%f - y:%f\n", s->s_list->x, s->s_list->y);
		calculate_projection(s, window, current_sprite);
		draw_vertical_stripe(s, ray, window);
		s_list_tmp = s_list_tmp->next;
		// i++;
	}
	my_lstfree(s->s_list);
}

//check out freeing and adding new sprite info > it-ray casts so many times!
// So slow when getting close to the sprite
