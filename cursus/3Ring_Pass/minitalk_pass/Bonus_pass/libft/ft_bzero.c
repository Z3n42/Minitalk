/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:11:22 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/03 18:08:22 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{	
	unsigned int	count;
	unsigned char	*str;

	str = (unsigned char *) s;
	count = 0;
	while (count < n)
	{
		str[count] = '\0';
		count++;
	}
}
