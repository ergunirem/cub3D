/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 17:42:28 by icikrikc      #+#    #+#                 */
/*   Updated: 2020/11/15 18:57:41 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char			*ptr_dest;
	unsigned char			*ptr_src;
	unsigned char			converted_c;
	size_t					i;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	converted_c = c;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		ptr_dest[i] = ptr_src[i];
		if (ptr_src[i] == converted_c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
