/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 15:37:02 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/06 19:29:21 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//implement bubble sort
void	sort_sprites()
{

}

//create sprite? save sprites in a linked list? and save its position in the map?
void	handle_sprite(t_window *window, t_ray *ray, t_list *s_list)
{
	t_list		*new;
	t_sprite	*sprite;

	sprite = (t_sprite*)malloc(sizeof(sprite));
	if (!sprite)
		exit_w_message("malloc failed\n", 1, window);
	sprite->x = ray->map_x;
	sprite->y = ray->map_y;
	new = ft_lstnew(sprite);
	if (!new)
		exit_w_message("ft_lstnew failed\n", 1, window);
	ft_lstadd_back(&s_list, new);
}

void	draw_sprites(t_window *window, t_ray *ray)
{
	//create s somewhere and link it to window and access it here;
	t_sprite_info	*s;
	t_player		*p;

	s = &window->s_info;
	p = window->player;
	//sort the sprites
	//draw sprites one by one with a loop that goes through the linked list
	while()
	{
		//calculate sprite_x and sprite_y
		s->sprite_x = sprite[index].x - p->pos_x;
		s->sprite_y = sprite[index].y - p->pos_y;
		//further calculations
		  //intDev, transform_x, transform_y, sprite_screen_x, sprite_height
			s->inv_det = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);
			s->transform_x = s->inv_det * (p->dir_y * s->sprite_x - p->dir_x * s->sprite_y);
			s->transform_y = s->inv_det * (-p->plane_y * s->sprite_x + p->plane_x * s->sprite_y);
			s->sprite_screen_x = (int)(window->width / 2) * (1 + s->transform_x / s->transform_y); //not sure about window->w
			s->sprite_height = fabs((int)(window->height/ s->transform_y));
		  //draw_start_y, draw_end_y, draw_start_x, draw_end_y
		  //check out stripe value?
		//pixels from string and black check
	}
	//free the linked list
}
