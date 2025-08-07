/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:55:39 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/06 18:54:44 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	numb;

	if (n < 0)
	{
		numb = (unsigned int)(n * (-1));
		write(fd, "-", 1);
	}
	else
	{
		numb = (unsigned int) n;
	}
	if (numb > 9)
	{
		ft_putnbr_fd (numb / 10, fd);
		ft_putnbr_fd (numb % 10, fd);
	}
	else
	{
		ft_putchar_fd (numb + '0', fd);
	}
}
