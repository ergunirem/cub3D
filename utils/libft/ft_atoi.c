/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 17:10:58 by icikrikc      #+#    #+#                 */
/*   Updated: 2020/11/18 13:11:51 by ergunirem     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static	int	skip_whitespace(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
			i++;
		else
			break ;
	}
	return (i);
}

static	int	ft_isdigit(const char c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	return (0);
}

int			ft_atoi(const char *str)
{
	int i;
	int result;
	int sign;

	result = 0;
	sign = 1;
	i = skip_whitespace(str);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		sign = 1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			break ;
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}
