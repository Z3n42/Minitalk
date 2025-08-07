/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 13:45:19 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/22 12:03:26 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_len(long n)
{
	int	counter;

	counter = 0;
	if (n < 0)
	{
		n = n * -1;
		counter++;
	}
	while (n > 9)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

static char	*ft_putnbr(long n, char *m)
{
	int		counter;

	counter = ft_len(n);
	m[counter + 1] = '\0';
	if (n == 0)
		m[0] = '0';
	if (n < 0)
	{
		n = n * -1;
		m[0] = '-';
	}
	while (n > 0)
	{
		m[counter] = (n % 10) + '0';
		n = (n / 10);
		counter--;
	}
	return (m);
}

char	*ft_itoa(int n)
{
	char			*array;
	int				counter;
	long			numb;

	numb = (long) n;
	array = (char *)malloc((ft_len(n) + 2) * sizeof(char));
	if (array == 0)
		return (NULL);
	counter = 0;
	return (ft_putnbr(numb, array));
}
