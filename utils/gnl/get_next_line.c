/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/01 07:53:02 by ergunirem     #+#    #+#                 */
/*   Updated: 2021/04/29 19:16:47 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

static int	find_newline(const char *s)
{
	int		len;
	int		i;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*get_line(char *container)
{
	int		index;
	char	*tmp;

	index = find_newline(container);
	if (index >= 0)
		tmp = ft_substr(container, 0, index);
	else
		tmp = ft_strdup(container);
	return (tmp);
}

static char	*update_container(char *container)
{
	int		index;
	char	*tmp;

	index = find_newline(container);
	if (index >= 0)
	{
		tmp = ft_strdup(&(container)[index + 1]);
		free(container);
	}
	else
	{
		free(container);
		tmp = NULL;
	}
	return (tmp);
}

static char	*append_buffer_to_container(char *container, char *buffer)
{
	char			*tmp;

	if (container == NULL)
		container = ft_strdup("");
	tmp = ft_strjoin(container, buffer);
	free(container);
	return (tmp);
}

int	get_next_line(int fd, char **line)
{
	static char		*container;
	char			buffer[100 + 1];
	int				result;

	if (fd < 0 || line == NULL)
		return (-1);
	result = 1;
	while (ft_strchr(container, '\n') == NULL && result > 0)
	{
		result = read(fd, buffer, 100);
		if (result < 0)
			return (-1);
		buffer[result] = '\0';
		container = append_buffer_to_container(container, buffer);
		if (container == NULL)
			return (-1);
	}
	*line = get_line(container);
	container = update_container(container);
	if (*line == NULL || (container == NULL && result != 0))
		return (-1);
	if (result == 0)
		return (0);
	return (1);
}
