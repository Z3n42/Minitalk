/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:24:40 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/15 14:04:03 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		count;
	int		len;
	char	*array;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s) + 1;
	array = (char *)malloc(len * sizeof(char));
	if (!array)
		return (NULL);
	count = 0;
	while (s[count] != '\0')
	{
		array[count] = f(count, s[count]);
		count++;
	}
	array[count] = '\0';
	return (array);
}	
