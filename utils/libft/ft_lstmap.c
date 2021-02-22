/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/17 13:13:53 by icikrikc      #+#    #+#                 */
/*   Updated: 2020/11/18 17:09:20 by ergunirem     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_lst;
	t_list *new_item;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_lst = NULL;
	while (lst != NULL)
	{
		if (!(new_item = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_item);
		lst = lst->next;
	}
	return (new_lst);
}
