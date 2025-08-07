/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 13:37:51 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/24 20:55:20 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include "libft/libft.h"

void	ft_handler1(int sig)
{
	static int		count;
	static int		c;

	if (count == 0)
		c = 255;
	if (sig == SIGUSR1)
		c = c | 128 >> count;
	else
		c = c ^ 128 >> count;
	count++;
	if (count == 8)
	{
		write(1, &c, 1);
		c = 255;
		count = 0;
	}
}

int	main(void)
{
	pid_t	pid;	

	pid = getpid();
	ft_printf("%d\n", pid);
	signal(SIGUSR1, ft_handler1);
	signal(SIGUSR2, ft_handler1);
	while (1)
		pause();
	return (0);
}
