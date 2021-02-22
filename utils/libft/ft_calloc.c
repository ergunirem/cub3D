/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ergunirem <ergunirem@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 21:13:47 by ergunirem     #+#    #+#                 */
/*   Updated: 2020/11/18 13:16:52 by ergunirem     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	if (count == 0 || size == 0)
	{
		ptr = (char*)malloc(sizeof(char) * 1);
		if (!ptr)
			return (NULL);
		ptr[0] = 0;
		return ((void*)ptr);
	}
	i = 0;
	ptr = (char*)malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < count * size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void*)ptr);
}
