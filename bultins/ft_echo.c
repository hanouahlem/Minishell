/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:09:33 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/12 19:00:34 by ahbey            ###   ########.fr       */
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

void	echo_if_n(t_parse *tab, int i)
{
	while (check_n(tab->args[i]) == 1)
		i++;
	while (tab->args[i])
	{
		if (!tab->args[i + 1])
			printf("%s", tab->args[i]);
		else
			printf("%s ", tab->args[i]);
		i++;
	}
}

int	ft_echo(t_parse *tab)
{
	int	i;

	i = 1;
	if (!tab->args[i])
		printf("\n");
	if (tab->args[i])
	{
		if (check_n(tab->args[i]) == 0)
		{
			while (tab->args[i])
				printf("%s ", tab->args[i++]);
			printf("\n");
		}
		else if (check_n(tab->args[i]) == 1)
		{
			echo_if_n(tab, i);
		}
	}
	return (0);
}

// bash-5.1$ echo bonjour > /dev/full
// bash: echo: write error: No space left on device


//echo :
// retirer les quotes
// si $a (donc une key qui existe pas) il faut echo rien et pas le "$a" a lecran