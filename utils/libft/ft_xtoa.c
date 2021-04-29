/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_xtoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 17:10:58 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/04/29 19:19:26 by icikrikc      ########   odam.nl         */
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
	while (number > 0)
	{
		number = number / 16;
		count++;
	}
	return (count);
}

static	char	hexadecimal_letter(int n)
{
	if (n < 10)
		return (n + '0');
	return ((n - 10) + 'a');
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
		str[len - 1] = hexadecimal_letter(n % 16);
		n = n / 16;
		len--;
	}
	return (str);
}

char	*ft_xtoa(unsigned long long int nbr)
{
	int		len;
	char	*str;
	long	n;

	n = nbr;
	len = get_digit_count(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	fill_in_str(str, n, len + 1);
	return (str);
}
