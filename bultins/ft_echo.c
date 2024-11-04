/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:09:33 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/30 21:02:12 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo max 2 fonctions 15 lignes chacune
// 	si le premier argument est "-n"
// 		pas de \n
// 	tant que les arguments sont -n
// 		i++
// 	et afficher le reste

// 	PAS OUBLIER
// 		echo -
// 		affiche -
// -n est valable que si ca commence par un tiret et que ya DES net export 
// echo
// 	si le premier argument est "-n"
// 		pas de \n
// 	tant que les arguments sont -n
// 		i++
// 	et afficher le reste

// 	PAS OUBLIER
// 		echo -
// 		affiche -
// -n est valable que si ca commence par un tiret et que ya DES n

// int	check_n(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str[i] && str[i] == '-' && str[i + 1] )
// 	{
// 		i++;
// 		while (str[i] && str[i] == 'n')
// 			i++;
// 		if (str[i] != 'n')
// 			return (1);
// 		else
// 			return (0);
// 	}
// 	return (1);
// }


int ft_echo (t_mini *data, t_parse *tab)
{
	// int	i;
	// int n;

	// i = 0;
	// n = 0;
	(void)data;
	(void)tab;
	// if (tab)
	// {
	// 	if (!check_n(tab->args[i]))
	// 	{
			
	// 	}
	// }
	// if(n == 0)
	// 	write(1,'\n', 1);
	return(0);
}


//bash-5.1$ echo bonjour > /dev/full
//bash: echo: write error: No space left on device
