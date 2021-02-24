/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstfree.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/17 13:15:28 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/02/24 17:57:42 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstfree(t_list **ptr_lst)
{
	t_list	*temp;

	if (!ptr_lst || !*ptr_lst)
		return ;
	while (*ptr_lst)
	{
		temp = (*ptr_lst)->next;
		free((*ptr_lst)->content);
		free(*ptr_lst);
		*ptr_lst = temp;
	}
	return ;
}
