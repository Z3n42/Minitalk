/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexmay.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 14:02:20 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/24 20:13:49 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

void	ft_putnbr_hexmay(unsigned int n, int fd, int *len)
{
	if (n > 15)
	{
		ft_putnbr_hexmay(n / 16, fd, len);
		ft_putnbr_hexmay(n % 16, fd, len);
	}
	else
	{
		(*len)++;
		if (n > 9)
			n += 7;
		ft_putchar_pfd(n + '0', fd);
	}
}
