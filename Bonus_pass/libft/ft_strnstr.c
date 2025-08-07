/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 10:31:00 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/07 19:41:39 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{	
	size_t	hcount;
	size_t	ncount;

	hcount = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[hcount])
	{
		ncount = 0;
		while (haystack[hcount + ncount] == needle[ncount])
		{
			if (ncount + hcount < len && needle[ncount + 1] == '\0')
				return ((char *)&haystack[hcount]);
			ncount++;
		}
		hcount++;
	}
	return (0);
}
