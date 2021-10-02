/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:39:15 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/01 19:14:45 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	count;

	count = 0;
	if (dst == NULL || src == NULL)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize != 0)
	{
		while (count < (dstsize - 1) && src[count] != '\0')
		{
			dst[count] = src[count];
			count++;
		}
		dst[count] = '\0';
		while (src [count] != '\0')
			count++;
	}
	return (count);
}
