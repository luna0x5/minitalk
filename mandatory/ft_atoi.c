/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:42:01 by hmoukit           #+#    #+#             */
/*   Updated: 2024/03/17 02:44:07 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	handle_overflow(const char *str, int sign, long result)
{
	long	nbr;
	size_t	i;

	nbr = 0;
	i = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		nbr = result * 10 + (str[i] - '0');
		if (nbr < result)
		{
			if (sign < 0)
				return (0);
			else if (sign > 0)
				return (-1);
		}
		result = nbr;
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= (-1);
		i++;
	}
	result = handle_overflow(str + i, sign, result);
	return (result);
}
