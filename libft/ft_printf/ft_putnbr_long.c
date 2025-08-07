/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:54:18 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/28 13:20:41 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

void	ft_putnbr_long(long n, int fd, int *len)
{
	if (n > 9)
	{
		ft_putnbr_long(n / 10, fd, len);
		ft_putnbr_long(n % 10, fd, len);
	}
	else
	{
		(*len)++;
		ft_putchar_pfd(n + '0', fd);
	}
}
