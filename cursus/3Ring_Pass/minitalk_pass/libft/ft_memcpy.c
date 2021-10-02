/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 18:26:24 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/20 21:38:49 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	unsigned int	count;

	s = (unsigned char *) src;
	d = (unsigned char *) dst;
	count = 0;
	if (dst == NULL && src == NULL)
		return (0);
	while (count < n)
	{
		d[count] = s[count];
		count++;
	}
	return (d);
}
