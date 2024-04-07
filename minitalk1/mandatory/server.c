/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:13:32 by hmoukit           #+#    #+#             */
/*   Updated: 2024/04/01 03:04:48 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	k = 7;
	static pid_t client_pid = -1;

	(void)context;
	if (client_pid == -1)
		client_pid = info->si_pid;
	else if (client_pid != info->si_pid)
	{
		k = 7;
		c = 0;
		client_pid = info->si_pid;
	}
	if (sig == SIGUSR1)
		c += 0 << k;
	else
		c += 1 << k;
	k--;
	if (k == -1)
	{
		write(1, &c, 1);
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
	newact.sa_flags = SA_SIGINFO;
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
