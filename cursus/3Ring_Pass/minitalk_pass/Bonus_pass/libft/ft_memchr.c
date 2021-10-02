/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 20:12:11 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/06 13:16:03 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	car;
	size_t			count;

	count = 0;
	str = (unsigned char *) s;
	car = (unsigned char) c;
	while (count < n)
	{
		if (str[count] == car)
			return (&str[count]);
		count ++;
	}
	return (NULL);
}
