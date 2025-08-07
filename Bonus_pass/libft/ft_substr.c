/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:30:18 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/21 15:33:28 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*array;
	unsigned char	*src;
	size_t			dstcount;

	src = (unsigned char *) s;
	dstcount = 0;
	if (!src)
		return (NULL);
	array = ((char *)malloc((len + 1) * sizeof(char)));
	if (!array)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		array[0] = '\0';
		return (array);
	}
	while (dstcount < len)
		array[dstcount++] = src[start++];
	array[dstcount] = '\0';
	return (array);
}
