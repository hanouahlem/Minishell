/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:19:49 by ahbey             #+#    #+#             */
/*   Updated: 2023/12/01 11:16:32 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*s1;

	if (!s)
		return (NULL);
	if (!ft_strlen(s))
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
		return (s1);
	}
	s1 = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!s1)
		return (NULL);
	i = 0;
	while (s[i])
	{
		s1[i] = (f)(i, s[i]);
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
