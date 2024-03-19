/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 06:11:09 by hmoukit           #+#    #+#             */
/*   Updated: 2024/03/19 05:08:27 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	k = 7;
	pid_t		client_pid;

	(void)context;
	client_pid = info->si_pid;
	if (sig == SIGUSR1)
		c += 0 << k;
	else
		c += 1 << k;
	k--;
	if (k == -1)
	{
		write(1, &c, 1);
		if (c == '\0')
			kill(client_pid, SIGUSR1);
		k = 7;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	newact;
	pid_t				pid;

	newact.sa_sigaction = signal_handler;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	pid = getpid();
	write(1, "\n----- the Process ID of the server -----\n\t\t", 44);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	while (1)
	{
		sigaction(SIGUSR1, &newact, NULL);
		sigaction(SIGUSR2, &newact, NULL);
		pause();
	}
	return (0);
}
