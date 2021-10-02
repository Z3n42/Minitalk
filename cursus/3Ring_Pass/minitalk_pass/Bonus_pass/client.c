/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:22:23 by ingonzal          #+#    #+#             */
/*   Updated: 2021/09/30 12:08:00 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include "libft/libft.h"

void	ft_handler2(int sig)
{
	if (sig == SIGUSR1)
		write(1, "OK\n", 3);
}

int	main(int argc, char **argv)
{
	char	*temp;
	int		count;
	int		counter;
	int		pid;

	if (argc != 3)
		ft_printf("Numero de paramatros inadecuado");
	signal(SIGUSR1, ft_handler2);
	pid = (ft_atoi(argv[1]));
	temp = argv[2];
	counter = -1;
	while (temp[++counter])
	{
		count = -1;
		while (++count < 8)
		{	
			usleep(50);
			if (temp[counter] & 128 >> count)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			pause();
		}
	}
	return (0);
}
