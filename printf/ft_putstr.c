/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:33:38 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/30 15:24:06 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str, int *len)
{
	int	i;

	(void)len;
	i = 0;
	(void)len;
	if (!str)
	{
		return (0);
	}
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	return (i);
}
