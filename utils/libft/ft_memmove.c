/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 17:30:56 by icikrikc      #+#    #+#                 */
/*   Updated: 2020/11/15 19:23:14 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	i = 0;
	while (i < len)
	{
		if (ptr_dest < ptr_src)
			ptr_dest[i] = ptr_src[i];
		else
			ptr_dest[len - i - 1] = ptr_src[len - i - 1];
		i++;
	}
	return (dest);
}
