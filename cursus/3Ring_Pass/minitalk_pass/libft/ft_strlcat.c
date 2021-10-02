/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:32:11 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/04 14:47:08 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	dstcount;

	count = ft_strlen(src);
	dstcount = 0;
	if (dstsize == 0)
		return (count);
	while (dst[dstcount] && dstcount < dstsize)
		dstcount++;
	count = count + dstcount;
	if (dstsize < ft_strlen(dst))
		return (count);
	while (dstsize - 1 > dstcount && *src)
	{
		dst[dstcount] = *src;
		src++;
		dstcount++;
	}
	dst[dstcount] = '\0';
	return (count);
}
