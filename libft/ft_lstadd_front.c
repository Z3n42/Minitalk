/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:22:00 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/18 14:53:53 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstadd_front(t_list **alst, t_list *new)
{
	if (!alst || !new)
		return (NULL);
	new->next = *alst;
	*alst = new;
	return (new);
}
