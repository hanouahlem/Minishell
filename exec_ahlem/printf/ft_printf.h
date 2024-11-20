/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:40:40 by ahbey             #+#    #+#             */
/*   Updated: 2023/12/20 16:59:00 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
void	ft_go_search(va_list args, const char *str, int *len, int *i);
int		ft_putchar(char c);
int		ft_putstr(char *str, int *len);
int		ft_putnbr(int n, int *len);
void	ft_putnbr_x(unsigned int n, int *len);
int		ft_putnbr_upper_x(unsigned int n, int *len);
void	ft_putnbr_p(unsigned long n, int *len);
void	ft_find_p(unsigned long n, int *len);
void	ft_putnbr_u(unsigned int n, int *len);

#endif
