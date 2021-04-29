/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 09:24:59 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/29 19:23:32 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

int	ft_putstr_fd_protected(char *s, int fd)
{
	size_t	len;
	int		ret_val;

	if (!s)
		return (-1);
	len = ft_strlen(s);
	ret_val = write(fd, s, len);
	return (ret_val);
}
