/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 12:47:42 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/29 19:21:42 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	get_word_count(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (i == 0 && s[i] != c)
			count++;
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static int	get_word_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s != '\0' && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static void	*ft_free_all(char **array, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		word_count;
	int		i;

	if (!s)
		return (NULL);
	word_count = get_word_count(s, c);
	array = (char **)malloc(sizeof(s) * (word_count + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (word_count > 0)
	{
		while (*s == c && *s != '\0')
			s++;
		array[i] = ft_substr(s, 0, get_word_len(s, c));
		if (!(array[i]))
			return (ft_free_all(array, i));
		s = s + get_word_len(s, c);
		i++;
		word_count--;
	}
	array[i] = NULL;
	return (array);
}
