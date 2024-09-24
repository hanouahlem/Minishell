/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:36:21 by ahbey             #+#    #+#             */
/*   Updated: 2023/11/16 15:53:15 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*int	main(void)
{
    char src[]="Hello, World!";
    char dest[]= "hahahaha";


    ft_memcpy(dest, src, 2);	    
    printf("Source : %s\n", src);
    printf("Destination : %s\n", dest);

    memcpy(dest, src, 2);
    printf("%s\n", dest);
    return 0;
}*/
