/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 06:11:07 by hmoukit           #+#    #+#             */
/*   Updated: 2024/04/01 03:05:13 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	client_signal_handler(int sig)
{
	if (sig == SIGUSR1)
		write(1, "Message received by server.\n", 28);
}

void	send_msg(char **av, int pid)
{
	int	i;
	int	j;

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
			usleep(400);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int		j;
	int		pid;
	char	c;

	c = '\0';
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		signal(SIGUSR1, client_signal_handler);
		send_msg(av, pid);
		j = 7;
		while (j >= 0)
		{
			if ((c >> j) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			j--;
			usleep(400);
		}
	}
	return (0);
}
