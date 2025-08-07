/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 19:56:12 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/07 20:25:59 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cont;

	cont = 0;
	if (n == 0)
		return (0);
	while ((s1[cont] != '\0' && s2[cont] != '\0' && cont < n - 1)
		&& s1[cont] == s2[cont])
	{
		cont++;
	}
	return ((unsigned char)s1[cont] - (unsigned char)s2[cont]);
}
