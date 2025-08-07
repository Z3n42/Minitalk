/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 13:37:51 by ingonzal          #+#    #+#             */
/*   Updated: 2021/09/30 12:05:25 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include "libft/libft.h"

void	ft_handler1(int sig, siginfo_t *sigact, void *context)
{
	static int		count;
	static int		c;

	context = NULL;
	if (count == 0)
		c = 255;
	if (sig == SIGUSR1)
	{
		c = c | 128 >> count;
		usleep(50);
	}
	else
	{
		c = c ^ 128 >> count;
		usleep(50);
	}
	count++;
	if (count == 8)
	{
		write(1, &c, 1);
		c = 255;
		count = 0;
	}
	kill(sigact->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sigact;
	pid_t				pid;	

	pid = getpid();
	ft_printf("%d\n", pid);
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = ft_handler1;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		pause();
	return (0);
}
