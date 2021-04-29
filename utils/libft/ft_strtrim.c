/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/17 12:56:35 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/29 19:20:09 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	int	get_left_offset(char const *s1, char const *set)
{
	int		i;
	int		offset;

	offset = 0;
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != NULL)
		i++;
	offset = i;
	return (offset);
}

static	int	get_right_offset(char const *s1, char const *set)
{
	int		len;
	int		offset;

	offset = 0;
	len = ft_strlen(s1);
	while (len > 0 && ft_strchr(set, s1[len - 1]) != NULL)
		len--;
	offset = len - 1;
	return (offset);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	int		offset_l;
	int		offset_r;
	int		i;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	offset_l = get_left_offset(s1, set);
	offset_r = get_right_offset(s1, set);
	if (offset_l > offset_r)
		return (ft_strdup(""));
	trimmed_str = (char *)malloc(sizeof(char) * (offset_r - offset_l + 2));
	if (!trimmed_str)
		return (NULL);
	i = 0;
	while (offset_l <= offset_r)
	{
		trimmed_str[i] = s1[offset_l];
		i++;
		offset_l++;
	}
	trimmed_str[i] = '\0';
	return (trimmed_str);
}
