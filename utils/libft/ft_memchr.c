/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 17:42:12 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/29 19:25:19 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	converted_c;

	p = (unsigned char *)s;
	converted_c = c;
	i = 0;
	while (i < n)
	{
		if (p[i] == converted_c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
