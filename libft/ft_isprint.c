/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:00:17 by ahbey             #+#    #+#             */
/*   Updated: 2023/11/16 15:56:59 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*#include <stdio.h>
#include <ctype.h>
int     main()
{
        printf("%d\n", ft_isprint('5'));
	printf("%d\n", ft_isprint(' '));
	printf("%d\n", ft_isprint('a'));
}*/
