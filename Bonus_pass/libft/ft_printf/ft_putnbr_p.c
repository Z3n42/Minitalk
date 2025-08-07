/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 14:03:02 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/24 20:14:15 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>
#include <stdint.h>

void	ft_putnbr_p(uintptr_t n, int fd, int *len)
{
	if (n > 15)
	{	
		ft_putnbr_p(n / 16, fd, len);
		ft_putnbr_p(n % 16, fd, len);
	}
	else
	{
		if (n > 9)
			n += 39;
		(*len)++;
		ft_putchar_pfd(n + '0', fd);
	}
}
