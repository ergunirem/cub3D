/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_sprites.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 21:18:14 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/09 23:31:22 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_lstfree(t_sprite *ptr_lst)
{
	t_sprite	*temp;

	if (!ptr_lst)
		return ;
	while (!ptr_lst->next)
	{
		temp = ptr_lst->next;
		if (ptr_lst->x > 0 && ptr_lst->y > 0)
			free(ptr_lst);
		ptr_lst = temp;
	}
	return ;
}

int	my_lstsize(t_sprite *lst)
{
	int		count;

	count = 0;
	while (lst->next != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_sprite	*my_lstlast(t_sprite *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	my_lstadd_back(t_sprite *lst, t_sprite *new)
{
	t_sprite	*last;
	t_sprite	*tmp;

	if (lst == NULL || new == NULL)
		return ;
	tmp = lst;
	// printf("p: %p\n", tmp->next);
	// printf("-x:%f - y:%f\n", lst->x, lst->y);
	// printf("-x:%f - y:%f\n", tmp->x, tmp->y);
	int i = 1;
	while (tmp->next != NULL)
	{
		if (tmp->x == new->x && tmp->y == new->y)
		{
			free(new);
			return ;
		}
		printf("%d > x:%f - y:%f\n", i, tmp->x, tmp->y);
		tmp = tmp->next;
		i++;
	}
	last = my_lstlast(lst);
	last->next = new;
}

//create sprite? save sprites in a linked list? and save its position in the map?

void	handle_sprite(t_window *window, t_ray *ray, t_sprite *s_list)
{
	t_sprite	*sprite;
	t_sprite	*sprite_tmp;
	int i;

	sprite = (t_sprite*)malloc(sizeof(t_sprite));
	if (!sprite)
		exit_w_message("malloc failed in handle_sprite\n", 1, window);
	sprite->x = ray->map_x;
	sprite->y = ray->map_y;
	sprite->next = NULL;
	// printf("x:%f - y:%f\n", sprite->x, sprite->y);
	my_lstadd_back(window->s_info->s_list, sprite);
}


// 2 starting sprite with -1, -1 in the list?
