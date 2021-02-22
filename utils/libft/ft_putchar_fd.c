/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 08:51:48 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/01/06 21:29:32 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int		ft_putchar_fd_protected(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (0);
}
