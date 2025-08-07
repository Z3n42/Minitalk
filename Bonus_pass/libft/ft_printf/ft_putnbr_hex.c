/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 19:52:22 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/24 20:13:34 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

void	ft_putnbr_hex(unsigned int n, int fd, int *len)
{
	if (n > 15)
	{
		ft_putnbr_hex(n / 16, fd, len);
		ft_putnbr_hex(n % 16, fd, len);
	}
	else
	{
		(*len)++;
		if (n > 9)
			n += 39;
		ft_putchar_pfd(n + '0', fd);
	}
}
