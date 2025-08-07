/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_pfd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:09:25 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/24 20:12:37 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

int	ft_putstr_pfd(char *s, int fd)
{
	int	count;

	count = 0;
	if (s == NULL)
	{
		write (fd, "(null)", 6);
		return (6);
	}
	while (s[count] != '\0')
	{
		write (fd, &s[count], 1);
		count++;
	}
	return (count);
}
