/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 06:11:09 by hmoukit           #+#    #+#             */
/*   Updated: 2024/04/16 15:06:11 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	send_back_sig(char c, pid_t client_pid)
{
	if (c == '\0')
		kill(client_pid, SIGUSR1);
}

void	ft_putstr(char *buffer, int count)
{
	write(1, buffer, count);
}

int	check_byte(char c)
{
	static int count = 1;

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

void initialize_buffer(char (*buffer)[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		(*buffer)[i] = 0;
		i++;
	}
}

void	handle_unicode(char c, int *count, int z)
{
	static char	buffer[4];
	static int	i;

	if (z == 1)
	{
		initialize_buffer(&buffer);
		i = 0;
	}
	if (*count > 1)
	{
		buffer[i] = c;
		i++;
		if (i == *count)
		{
			write(1, buffer, i);
			i = 0;
			*count = 0;
			initialize_buffer(&buffer);
		}
	}
}

void	make_char(char *c, int sig, int *k, pid_t c_pid)
{
	static int count = 0;
	if (sig == SIGUSR1)
		*c += 0 << *k;
	else
		*c += 1 << *k;
	(*k)--;
	if (*k == -1)
	{
		if (count == 0)
			count = check_byte(*c);
		if (count == 1)
		{
			write(1, &(*c), 1);
			count = 0;
			if (*c == '\0')
				kill(c_pid, SIGUSR1);
		}
		else
		{
			handle_unicode(*c, &count, 0);
			if (*c == '\0')
				kill(c_pid, SIGUSR1);
		}
		*c = 0;
		*k = 7;
	}
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	k = 7;
	static pid_t client_pid = -1;
	int count = 0;
	(void)context;
	if (client_pid == -1)
		client_pid = info->si_pid;
	else if (client_pid != info->si_pid)
	{
		c = 0;
		k = 7;
		handle_unicode(c, &count, 1);
		client_pid = info->si_pid;
	}
	make_char(&c, sig, &k, client_pid);
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
