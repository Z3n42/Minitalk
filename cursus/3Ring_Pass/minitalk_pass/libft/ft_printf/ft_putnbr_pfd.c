/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pfd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:55:39 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/24 20:15:00 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

void	ft_putnbr_pfd(int n, int fd, int *len)
{
	unsigned int	numb;

	if (n < 0)
	{
		(*len)++;
		numb = (unsigned int)(n * (-1));
		write(fd, "-", 1);
	}
	else
		numb = (unsigned int) n;
	if (numb > 9)
	{
		ft_putnbr_pfd (numb / 10, fd, len);
		ft_putnbr_pfd (numb % 10, fd, len);
	}
	else
	{
		(*len)++;
		ft_putchar_pfd (numb + '0', fd);
	}
}
