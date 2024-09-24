/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:41:59 by ahbey             #+#    #+#             */
/*   Updated: 2023/11/27 17:57:28 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	c2;
	size_t			i;

	str = (unsigned char *)s;
	c2 = (unsigned char)c;
	i = 0;
	while (i < n && str[i] != c2)
		i++;
	if (i == n)
		return (NULL);
	return ((void *)&str[i]);
}
/*int main()
{
    const char *str = "hello, world!";
    char chercher = 'o';

    const char *resultat = ft_memchr(str, chercher, 3);

    if(resultat != NULL)
    printf(" %s\n", resultat);

    else
    printf("caractere non touver\n");

  return (0);  
}*/
