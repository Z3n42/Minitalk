/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:25:44 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/20 21:41:29 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*array;
	size_t	max;
	int		counter;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	max = (ft_strlen(s1)) + (ft_strlen(s2));
	array = ((char *)malloc((max + 1) * (sizeof(char))));
	if (array == NULL)
		return (NULL);
	counter = 0;
	while (i < ft_strlen(s1))
		array[counter++] = s1[i++];
	i = 0;
	while (i < ft_strlen(s2))
		array[counter++] = s2[i++];
	array[counter] = '\0';
	return (array);
}
