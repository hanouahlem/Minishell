/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:20:51 by ahbey             #+#    #+#             */
/*   Updated: 2023/12/26 12:42:03 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_go_search(va_list args, const char *str, int *len, int *i)
{
	if (str[*i + 1] == 'c')
		*len += ft_putchar(va_arg(args, int));
	else if (str[*i + 1] == 's')
		*len += ft_putstr(va_arg(args, char *), len);
	else if (str[*i + 1] == 'p')
		ft_find_p(va_arg(args, unsigned long), len);
	else if (str[*i + 1] == 'd' || str[*i + 1] == 'i')
		ft_putnbr(va_arg(args, int), len);
	else if (str[*i + 1] == 'u')
		ft_putnbr_u(va_arg(args, unsigned int), len);
	else if (str[*i + 1] == 'x')
		ft_putnbr_x(va_arg(args, unsigned int), len);
	else if (str[*i + 1] == 'X')
		ft_putnbr_upper_x(va_arg(args, unsigned int), len);
	else if (str[*i + 1] == '%')
		*len += ft_putchar('%');
	(*i)++;
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		len;

	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_go_search(args, str, &len, &i);
		}
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}

/*int main()
{
	printf("len vrai = %d\n", printf("hello %"));
	printf("len = %d\n",ft_printf("hello %"));
}*/
