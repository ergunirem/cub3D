/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 09:05:50 by icikrikc      #+#    #+#                 */
/*   Updated: 2020/11/18 17:13:12 by ergunirem     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	int		i;
	char	*tmp;

	tmp = NULL;
	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == c)
			tmp = (char *)s + i;
		i++;
	}
	return (tmp);
}
