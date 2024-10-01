/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:44:02 by ahbey             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/26 15:40:38 by ahbey            ###   ########.fr       */
=======
/*   Updated: 2024/09/18 18:59:19 by manbengh         ###   ########.fr       */
>>>>>>> MANAAAAAR
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_quote(char *str)
// {
// 	int		i;
// 	char	c;
// 	int		flag;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '"' || str[i] == '\'')
// 		{
// 			c = str[i];
// 			flag = 1;
// 			i++;
// 			while (str[i])
// 			{
// 				if (str[i] == c)
// 				{
// 					flag = 0;
// 					break ;
// 				}
// 				i++;
// 			}
// 		}
// 		i++;
// 	}
// 	if (flag == 1)
// 		return (printf("error : syntax\n"), 1);
// 	return (0);
// }

int	ft_check_quote(char *str, int *i, char c)
{
	int	flag;

	flag = 1;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == c)
		{
			flag = 0;
			break ;
		}
		(*i)++;
	}
	return (flag);
}

int	ft_quote(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			flag = ft_check_quote(str, &i, str[i]);
			if (flag == 1)
				break ;
		}
		i++;
	}
	if (flag == 1)
		return (printf("error : syntax\n"), 1);
	return (0);
}

int	ft_check_redir_in_out(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<')
		{
			return (printf("Error : syntax"), 1);
		}
		i++;
	}
	return (0);
}
