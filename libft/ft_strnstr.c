/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:23:00 by ahbey             #+#    #+#             */
/*   Updated: 2023/11/27 17:59:54 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	if (n == 0)
		return (NULL);
	while (str[i] != '\0' && i < n)
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			while (i + j < n && str[i + j] == to_find[j])
			{
				j++;
				if (!to_find[j])
					return ((char *)&str[i]);
			}
		}
		i++;
	}
	return (0);
}
/*int main()
{
	const char str[30]= "hello comment tu vas ?";
 	const char to_find[]= "comment";
	char *resultat = ft_strnstr(str, to_find, 20);
 	printf("find = %s\n", resultat);
 	printf("find = %s\n",ft_strnstr(str, to_find, 2));

}*/
