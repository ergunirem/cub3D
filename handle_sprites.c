/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_sprites.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 21:18:14 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/22 16:34:25 by icikrikc      ########   odam.nl         */
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
	while (lst)
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
	while (tmp)
	{
		if (tmp->x == new->x && tmp->y == new->y)
		{
			free(new);
			return ;
		}
		// if (tmp->x == 0 && tmp->y == 0)
		// {
		// 	tmp->x = new->x;
		// 	tmp->y = new->y;
		// 	tmp->dist = new->dist;
		// 	free(new);
		// 	return ;
		// }
		tmp = tmp->next;
	}
	last = my_lstlast(lst);
	last->next = new;
}

/*
save sprites in a linked list and save its position in the map
*/

void	handle_sprite(t_window *window, t_ray *ray, t_sprite *s_list)
{
	t_sprite	*sprite;
	t_sprite	*head;
	int			i;

	sprite = (t_sprite*)malloc(sizeof(t_sprite));
	if (!sprite)
		exit_w_message("malloc failed in handle_sprite\n", 1, window);
	sprite->x = ray->map_x;
	sprite->y = ray->map_y;
	sprite->dist = ray->perp_wall_dist;
	sprite->next = NULL;
	// head = s_list;
	// if (head->x == 0 && head->y == 0)
	// {
	// 	head->x = ray->map_x;
	// 	head->y = ray->map_y;
	// }
	my_lstadd_back(window->s_info->s_list, sprite);
}
