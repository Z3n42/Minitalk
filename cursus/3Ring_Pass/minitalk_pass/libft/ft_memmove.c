/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:36:08 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/20 21:39:55 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;
	unsigned int	count;

	s = (unsigned char *) src;
	d = (unsigned char *) dst;
	count = 0;
	if (dst == NULL && src == NULL)
		return (0);
	if (dst <= src)
	{
		while (count < len)
		{
			d[count] = s[count];
			count++;
		}
	}
	else
	{
		count = len;
		while (count--)
			d[count] = s[count];
	}
	return (d);
}
