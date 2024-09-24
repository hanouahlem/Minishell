/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:49:07 by ahbey             #+#    #+#             */
/*   Updated: 2023/11/16 15:55:58 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
/*#include <stdio.h>
#include <ctype.h>
int	main()
{
	printf("%d\n",ft_isalnum('5'));
	printf("%d\n",ft_isalnum('E'));
	printf("%d\n",ft_isalnum('a'));
	printf("%d\n",ft_isalnum('*'));

}*/
