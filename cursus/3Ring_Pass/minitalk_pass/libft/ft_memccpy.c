/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 18:34:32 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/06 13:26:56 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			count;
	unsigned char	f;

	f = (unsigned char) c;
	s = (unsigned char *) src;
	d = (unsigned char *) dst;
	count = 0;
	while (count < n)
	{
		if (s[count] == f)
		{
			d[count] = s[count];
			return (d + count + 1);
		}
		d[count] = s[count];
		count++;
	}
	return (NULL);
}
