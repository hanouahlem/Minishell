/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:29:33 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/07 18:51:53 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_negation(char *str)
{
	int	i;
	int	flag_quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == SQUOTE || str[i] == DQUOTE)
		{
			flag_quote = str[i];
			i++;
			while (str[i] != flag_quote)
			{
				str[i] = -str[i];
				i++;
			}
		}
		i++;
	}
	return (str);
}
void token_positive(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			str[i] = -str[i];
		i++;
	}
}

char	*delete_quote(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == SQUOTE || str[i] == DQUOTE)
		{
			i++;
		}
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	free(str);
	return (res);
}
