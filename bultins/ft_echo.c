/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:09:33 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/31 17:14:43 by manbengh         ###   ########.fr       */
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


int	check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-' && str[i + 1])
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] && str[i] != 'n')
			return (0);
		else
			return (1);
	}
	return (0);
}

int ft_echo(t_mini *data, t_parse *tab)
{
	int	i;

	i = 1;
	(void)data;
	if (!tab->args[i])
		printf("\n");
	if (tab->args[i])
	{
		if (check_n(tab->args[i]) == 0 /*&& tab->args[i + 1]*/)
		{
			while (tab->args[i])
			{
				printf("%s ", tab->args[i]);
				i++;
			}
			printf("\n");
		}
		else if (check_n(tab->args[i]) == 1 /*&& tab->args[i + 1]*/)
		{
			i++;
			while (tab->args[i])
			{
				printf("%s ", tab->args[i]);
				i++;
			}
		}
	}
	return(0);
}
