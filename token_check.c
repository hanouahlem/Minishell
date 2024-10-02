/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:29:33 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/02 15:53:21 by ahbey            ###   ########.fr       */
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
