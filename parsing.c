/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:44:02 by ahbey             #+#    #+#             */
/*   Updated: 2024/09/18 18:48:47 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote(char *str)
{
	int		i;
	char	c;
	int		flag;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			flag = 1;
			i++;
			while (str[i])
			{
				if (str[i] == c)
				{
					flag = 0;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	if (flag == 1)
		return (printf("error : quot de veau\n"), 1);
	return (0);
}

int	ft_fleche(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

// ft_error_syntax(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while(str[i])
// 	{
// 		if(str[i] == '<' || str[i]== '>')
// 	}
// }
