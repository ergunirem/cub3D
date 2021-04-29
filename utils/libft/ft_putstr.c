/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 09:24:59 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/29 19:23:14 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putstr(char *s)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(1, s, len);
}

int	ft_putstr_protected(char *s)
{
	size_t	len;
	int		ret_val;

	if (!s)
		return (-1);
	len = ft_strlen(s);
	ret_val = write(1, s, len);
	return (ret_val);
}
