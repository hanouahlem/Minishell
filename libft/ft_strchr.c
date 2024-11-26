/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:57:08 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/25 15:32:24 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ((char)c))
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}
// int	main(void)
// {
	// const char s[] = "hello world";
// 	char const s[]= "//je su//is la///";
// 	printf("%s\n", ft_strchr(s, '/'));
// 	printf("%s", strchr(s, '/'));
// }
