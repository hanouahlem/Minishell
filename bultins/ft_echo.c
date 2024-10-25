/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:09:33 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/24 19:19:34 by ahbey            ###   ########.fr       */
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

int ft_echo (t_mini *data, t_parse *tab)
{
	printf("cmd ---> %s\n", tab->args[0]);
	if (tab->args[0])
	{
		
	}
	(void)data;
	printf("hello echo\n");
	return(0);
}
