/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 15:37:02 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/26 16:42:42 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite	*swap(t_sprite *s_one, t_sprite *s_two, int *swapped)
{
	t_sprite	*tmp;

	tmp = s_two->next;
	s_two->next = s_one;
	s_one->next = tmp;
	*swapped = 1;
	return (s_two);
}

/*
It bubble sorts the sprites list based on distance (perp_wall_dist)
*/

void	sort_sprites(int num_sprites, t_sprite **s_list, int i, int j)
{
	t_sprite	**head;
	t_sprite	*s_one;
	t_sprite	*s_two;
	int			swapped;

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
				*head = swap(s_one, s_two, &swapped);
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
	s->trans_x = s->inv_det * (p->dir_y * s->sprite_x - p->dir_x * s->sprite_y);
	s->trans_y = s->inv_det * (-p->plane_y * s->sprite_x
			+ p->plane_x * s->sprite_y);
	s->s_screen_x = (int)(window->width / 2) * (1 + s->trans_x / s->trans_y);
	s->s_height = abs((int)(window->height / s->trans_y));
	s->draw_start_y = -s->s_height / 2 + window->height / 2;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->s_height / 2 + window->height / 2;
	if (s->draw_end_y >= window->height)
		s->draw_end_y = window->height - 1;
	s->s_width = abs((int)(window->height / s->trans_y));
	s->draw_start_x = -s->s_width / 2 + s->s_screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->s_width / 2 + s->s_screen_x;
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

void	draw_vertical_stripe(t_sprite_info *s, t_ray *ray, t_window *win)
{
	int	color;

	s->stripe = s->draw_start_x;
	while (s->stripe < s->draw_end_x)
	{
		s->tex_x = (int)(256 * (s->stripe - (-s->s_width / 2 + s->s_screen_x))
				* win->textures->sprite->width / s->s_width)
			/ win->textures->sprite->line_length;
		if (s->trans_y > 0 && s->stripe > 0 && s->stripe < win->width
			&& s->trans_y < ray->z_buffer[s->stripe])
		{
			s->y = s->draw_start_y;
			while (s->y < s->draw_end_y)
			{
				s->d = (s->y) * 256 - win->height * 128 + s->s_height * 128;
				s->tex_y = ((s->d * 64) / s->s_height) / 256; //change 64 here: it's actually tex_height but there is a problem with it
				color = my_mlx_pixel_get(win->textures->sprite, s->tex_x, s->tex_y);
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_set(win->image, s->stripe, s->y, color);
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
	t_sprite		*tmp_list;
	int				i;

	s = malloc(sizeof(t_sprite_info));
	if (!s)
		ft_exit("Malloc failed\n", window);
	ft_bzero(s, sizeof(t_sprite_info));
	s_list = window->s_list;
	tmp_list = s_list;
	s->num_sprites = my_lstsize(s_list);
	sort_sprites(s->num_sprites, &s_list, 0, 0);
	i = 0;
	while (i < s->num_sprites)
	{
		do_projection(s, window, s_list);
		draw_vertical_stripe(s, ray, window);
		s_list = s_list->next;
		i++;
	}
	free(s);
	my_lstfree(&tmp_list);
}
