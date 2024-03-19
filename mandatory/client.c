/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:13:30 by hmoukit           #+#    #+#             */
/*   Updated: 2024/03/18 03:43:42 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int ac, char **av)
{
	int	i;
	int	j;
	int	pid;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		i = 0;
		while (av[2][i])
		{
			j = 7;
			while (j >= 0)
			{
				if ((av[2][i] >> j) & 1)
					kill(pid, SIGUSR2);
				else
					kill(pid, SIGUSR1);
				j--;
				usleep(500);
			}
			i++;
		}
	}
	return (0);
}
