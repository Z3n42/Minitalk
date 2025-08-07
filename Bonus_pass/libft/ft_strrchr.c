/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:20:29 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/01 19:03:44 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	pos;
	int	count;

	pos = 0;
	count = 0;
	while (str[count] != '\0')
	{
		if (str[count] == c)
		{
			pos = count;
		}
		count++;
	}
	if (c == '\0' && pos == 0)
		return ((char *)str + count);
	if (pos == 0 && c != '\0' && str[pos] != c)
		return (0);
	return ((char *)str + pos);
}
