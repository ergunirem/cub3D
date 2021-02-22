/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ergunirem <ergunirem@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 10:04:55 by ergunirem     #+#    #+#                 */
/*   Updated: 2020/12/09 12:32:08 by ergunirem     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	int		len;
	int		i;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *src)
{
	int		len;
	int		i;
	char	*copy;

	len = ft_strlen(src);
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_s;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	sub_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_s[i] = s[start + i];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	joined_str = (char *)malloc(sizeof(char) *
		(ft_strlen(s1) + ft_strlen(s2) + 1));
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
