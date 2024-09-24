/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:02:24 by ahbey             #+#    #+#             */
/*   Updated: 2023/11/16 15:58:29 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (s && *f)
	{
		i = 0;
		while (s[i])
		{
			(*f)(i, &(s[i]));
			i++;
		}
	}
}
/*#include <stdio.h>

void afficherCaractere(unsigned int index, char *caractere)
{
    printf("Caractère à l'index %u : %c\n", index, *caractere);
}

int main()
{
    char maChaine[] = "Hello, World!";

    // Utilisation de ft_striteri avec la fonction afficherCaractere
        ft_striteri(maChaine, afficherCaractere);

    return 0;
}*/
