/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:45:52 by ahbey             #+#    #+#             */
/*   Updated: 2023/11/21 17:58:07 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest[i] && !src[i])
		return (0);
	while ((i < n - 1) && src[i] != '\0' && (n != 0))
	{
		dest[i] = src[i];
		i++;
	}
	if (n != 0)
		dest[i] = '\0';
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}
/*int	main()
{

	char dest[] = "oui";
	const char src[]= "Hello, world!";
    
	printf("%ld\n", ft_strlcpy(dest, src, 0));
	printf("%s", dest);
}*/
