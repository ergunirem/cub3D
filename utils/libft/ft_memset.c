/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 17:41:42 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/29 19:24:51 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	converted_c;

	p = (unsigned char *)s;
	converted_c = c;
	while (n > 0)
	{
		*p = converted_c;
		p++;
		n--;
	}
	return (s);
}
