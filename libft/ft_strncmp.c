/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:13:51 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/30 15:18:27 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
		i++;
	return ((unsigned char )s1[i] - (unsigned char )s2[i]);
}
// #include <stdio.h>
// #include <string.h>

// int     main()
// {
//         unsigned int n = 5;
//         char    s1[] = "hellk";
//         char    s2[] = "hello";

//         printf("la difference est de : %d\n", ft_strncmp(s1, s2, n));
// 	printf("la difference est de : %d\n", strncmp(s1, s2, n));
// }