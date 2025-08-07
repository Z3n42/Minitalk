/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:46:09 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/20 21:41:07 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*array;
	int		count;

	count = 0;
	while (s1[count] != '\0')
		count++;
	array = ((char *)malloc((count + 1) * sizeof(char)));
	if (array == NULL)
		return (NULL);
	count = 0;
	while (s1[count] != '\0')
	{
		array[count] = s1[count];
		count++;
	}
	array[count] = '\0';
	return (array);
}
