/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 15:37:02 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/20 17:06:03 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite *swap(t_sprite *s_one, t_sprite *s_two)
{
	t_sprite *tmp;

	tmp = s_two->next;
	s_two->next = s_one;
	s_one->next = tmp;
	return (s_two);
}

void print_list(t_sprite *s_list, int i)
{
	while (s_list)
	{
		// printf("%d x: %f y: %f\n", i, s_list->x, s_list->y);
		printf("Dist %d: %f\n", i, s_list->dist);
		s_list = s_list->next;
		i++;
	}
}

/*
It bubble sorts the sprites list based on distance (perp_wall_dist)
*/

void	sort_sprites(int num_sprites, t_sprite **s_list, int i, int j)
{
	t_sprite **head;
	t_sprite *s_one;
	t_sprite *s_two;
	int	swapped;

	while (i <= num_sprites)
	{
		head = s_list;
		swapped = 0;
		j = 0;
		while (j < num_sprites - i - 1)
		{
			s_one = *head;
			s_two = s_one->next;
			if (s_one->dist < s_two->dist)
			{
				*head = swap(s_one, s_two);
				swapped = 1;
			}
			head = &(*head)->next;
			j++;
		}
		if (swapped == 0)
			break ;
		i++;
	}
}

/*
It projects each sprite, calculates the size it should have on screen.
First, translates sprite position to relative to camera. Then, calculates
lowest and highest pixel to fill in current stripe.
*/

void	do_projection(t_sprite_info *s, t_window *window, t_sprite *sprite)
{
	t_player	*p;

	p = window->player;
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

void	draw_vertical_stripe(t_sprite_info *s, t_ray *ray, t_window *window)
{
	int	color;

	s->stripe = s->draw_start_x;
	while (s->stripe < s->draw_end_x)
	{
		s->tex_x = (int)(256 * (s->stripe - (-s->sprite_width / 2 + s->sprite_screen_x))
			* window->textures->sprite->width / s->sprite_width) / window->textures->sprite->line_length;
		if (s->transform_y > 0 && s->stripe > 0 && s->stripe < window->width
			&& s->transform_y < ray->z_buffer[s->stripe])
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
	t_sprite		*s_list;
	t_player		*p;
	int				i;

	// if (!s->s_list)
	// 	ft_exit("empty sprite list\n", window);
	s = window->s_info;
	s_list = s->s_list;
	s->num_sprites = my_lstsize(s_list);
	print_list(s_list, 0);
	sort_sprites(s->num_sprites, &s_list, 0, 0);
	printf("after\n");
	print_list(s_list, 0);
	i = 0;
	while (i < s->num_sprites)
	{
		do_projection(s, window, s_list);
		draw_vertical_stripe(s, ray, window);
		s_list = s_list->next;
		i++;
	}
	// if (s_list->next)
	// 	my_lstfree(s_list); //segv when no sprite is available
}
