/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 09:05:50 by icikrikc      #+#    #+#                 */
/*   Updated: 2020/11/17 19:31:36 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;

	if (*needle == '\0')
		return ((char *)(haystack));
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == *needle)
		{
			k = 0;
			while (needle[k] != '\0' && i + k < len)
			{
				if (needle[k] != haystack[i + k])
					break ;
				k++;
			}
			if (needle[k] == '\0')
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
