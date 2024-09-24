/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:45:03 by ahbey             #+#    #+#             */
/*   Updated: 2023/11/30 11:38:33 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	end;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[i]))
	{
		i++;
	}
	while (ft_strchr(set, s1[end]))
	{
		end--;
	}
	dest = ft_substr(s1, i, (end - i + 1));
	return (dest);
}
// int main()
// {
// 	char const s[]= "//je su//is la//";
// 	char const set[]= "//";

// 	printf("%s", ft_strtrim(s, set));

// }
