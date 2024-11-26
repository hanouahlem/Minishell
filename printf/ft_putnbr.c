/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:24:55 by ahbey             #+#    #+#             */
/*   Updated: 2024/07/06 19:40:29 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n, int *len)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		*len += write(2, "-", 1);
		nb = nb * -1;
	}
	if (nb > 9)
		ft_putnbr(nb / 10, len);
	*len += write(2, &"0123456789"[nb % 10], 1);
	return (0);
}

void	ft_putnbr_u(unsigned int n, int *len)
{
	if (n > 9)
		ft_putnbr_u(n / 10, len);
	*len += write(2, &"0123456789"[n % 10], 1);
}
