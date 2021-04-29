/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/17 12:45:24 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/29 19:20:54 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	joined_str = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined_str)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
	{
		joined_str[i] = *s1;
		s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		joined_str[i] = *s2;
		s2++;
		i++;
	}
	joined_str[i] = '\0';
	return (joined_str);
}

char	*ft_strjoin_free(char const *s1, char const *s2, int nbr)
{
	char	*joined_str;

	joined_str = ft_strjoin(s1, s2);
	if (!joined_str)
		return (NULL);
	if (nbr == 1 || nbr == 3)
		free((void *)s1);
	if (nbr == 2 || nbr == 3)
		free((void *)s2);
	return (joined_str);
}
