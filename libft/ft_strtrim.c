/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:14:28 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/21 22:00:27 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_compare(char c, const char *set)
{
	size_t	setcount;

	setcount = 0;
	while (set[setcount])
	{
		if (set[setcount] == c)
			return (1);
		setcount++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	s1count;
	int				len;
	char			*array;
	size_t			total;

	if (!s1)
		return (NULL);
	s1count = 0;
	len = ft_strlen(s1) - 1;
	total = len;
	while (ft_compare(s1[s1count], set) == 1)
		s1count++;
	while ((len >= 0) && (ft_compare(s1[len], set) == 1))
		len--;
	if (total == s1count)
		array = ft_substr(s1, s1count, 1);
	else
		array = ft_substr(s1, s1count, (len - s1count) + 1);
	return (array);
}
