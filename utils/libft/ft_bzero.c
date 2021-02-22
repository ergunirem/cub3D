/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ergunirem <ergunirem@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 19:51:57 by ergunirem     #+#    #+#                 */
/*   Updated: 2020/11/18 13:08:45 by ergunirem     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*c;
	size_t			i;

	c = s;
	i = 0;
	while (i < n)
	{
		c[i] = '\0';
		i++;
	}
}
