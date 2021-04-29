/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 17:10:58 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/29 19:28:05 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	int	get_digit_count(long number)
{
	int	count;

	count = 0;
	if (number <= 0)
	{
		count++;
		number = -number;
	}
	while (number != 0)
	{
		number = number / 10;
		count++;
	}
	return (count);
}

static	char	*fill_in_str(char *str, long n, int len)
{
	str[len - 1] = '\0';
	len--;
	if (n == 0)
	{
		str[len - 1] = '0';
		return (str);
	}
	while (n > 0)
	{
		str[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int nbr)
{
	int			len;
	char		*str;
	long long	n;

	n = nbr;
	len = get_digit_count(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	fill_in_str(str, n, len + 1);
	return (str);
}

char	*ft_uitoa(unsigned int nbr)
{
	int					len;
	char				*str;
	unsigned long long	n;

	n = nbr;
	len = get_digit_count(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	fill_in_str(str, n, len + 1);
	return (str);
}
