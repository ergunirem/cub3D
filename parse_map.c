/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 15:30:38 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/02/23 21:14:50 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(t_window *window, char *line, t_list *map_list)
{
	int		i;
	t_list	*new;

	window->map->map_started = TRUE;
	i = 0;
	while (line[i])
	{
		if (ft_strchr("012NSEW ", line[i]) == NULL)
			exit_w_message("invalid char inside map\n", 1, window);
		i++;
	}
	new = ft_lstnew(line);
	//printf("%s\n", new->content);
	if (!new)
		exit_w_message("ft_lstnew failed\n", 1, window);
	ft_lstadd_back(&map_list, new);
	//printf("%s\n", ft_lstlast(map_list)->content);
	//printf("%s\n", map_list->content);
}

