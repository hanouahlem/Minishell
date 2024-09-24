/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:09:03 by ahbey             #+#    #+#             */
/*   Updated: 2023/11/24 12:07:16 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t n)
{
	char	*s;

	if (n && (nmemb > SIZE_MAX / n))
		return (NULL);
	s = malloc(n * nmemb);
	if (!s)
		return (NULL);
	ft_bzero(s, nmemb * n);
	return (s);
}
/*int main()	
{
	int *str;
	int i = 0;
	str = ft_calloc(sizeof(int), 8);
	
	while (i < 8)
	{
		 printf("%d\n", str[i]);
		 i++;
	}
	return (0);
}*/
