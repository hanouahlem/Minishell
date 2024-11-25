/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:29:53 by ahbey             #+#    #+#             */
/*   Updated: 2024/07/06 19:40:05 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_x(unsigned int n, int *len)
{
	unsigned long	nb;

	nb = n;
	if (nb >= 16)
		ft_putnbr_x(nb / 16, len);
	*len += write(2, &"0123456789abcdef"[nb % 16], 1);
}

int	ft_putnbr_upper_x(unsigned int n, int *len)
{
	unsigned long	nb;

	nb = n;
	if (nb >= 16)
		ft_putnbr_upper_x(nb / 16, len);
	*len += write(2, &"0123456789ABCDEF"[nb % 16], 1);
	return (0);
}

void	ft_putnbr_p(unsigned long n, int *len)
{
	unsigned long	nb;

	nb = n;
	if (nb >= 16)
		ft_putnbr_p(nb / 16, len);
	*len += write(2, &"0123456789abcdef"[nb % 16], 1);
}

void	ft_find_p(unsigned long n, int *len)
{
	if (n == 0)
		*len += write(2, "(nil)", 5);
	else
	{
		*len += write(2, "0x", 2);
		ft_putnbr_p(n, len);
	}
}
