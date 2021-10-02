/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:22:23 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/25 13:00:44 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include "libft/libft.h"

int	main(int argc, char **argv)
{
	char	*temp;
	int		count;
	int		counter;
	int		pid;

	if (argc != 3)
		ft_printf("Numero de paramatros inadecuado");
	pid = (ft_atoi(argv[1]));
	temp = argv[2];
	counter = 0;
	while (temp[counter])
	{
		count = 0;
		while (count < 8)
		{	
			if (temp[counter] & 128 >> count)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			count++;
			usleep(50);
		}
		counter++;
	}
	return (0);
}
