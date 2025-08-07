/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:00:08 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/28 13:23:01 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stddef.h>
# include <stdint.h>

int		ft_putchar_pfd(char c, int fd);
int		ft_putstr_pfd(char *s, int fd);
void	ft_putnbr_pfd(int n, int fd, int *len);
void	ft_putnbr_long(long n, int fd, int *len);
void	ft_putnbr_hex(unsigned int n, int fd, int *len);
void	ft_putnbr_hexmay(unsigned int n, int fd, int *len);
void	ft_putnbr_p(uintptr_t n, int fd, int *len);
int		ft_printf(const char *format, ...);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
