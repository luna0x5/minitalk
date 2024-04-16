/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:19:25 by hmoukit           #+#    #+#             */
/*   Updated: 2024/04/16 17:02:41 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	initialize_buffer(char (*buffer)[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		(*buffer)[i] = 0;
		i++;
	}
}

int	check_byte(char c)
{
	static int	count = 1;

	if (count == 1)
	{
		if ((c & 0xC0) == 0xC0)
			count = 2;
		if ((c & 0xE0) == 0xE0)
			count = 3;
		if ((c & 0xF0) == 0xF0)
			count = 4;
	}
	return (count);
}
