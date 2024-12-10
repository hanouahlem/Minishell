/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:21:43 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/10 14:02:43 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_hd(t_mini *data)
{
	int	i;

	i = 0;
	while (data->token)
	{
		if (data->token->type == DBL_REDIR_IN)
			i++;
		data->token = data->token->next;
	}
	return (i);
}

char	take_delimiter(t_mini *data)
{
	int	i;
	char *str;
	
	i = 0;
	while (i < data->nbr_hd && data->parser)
	{
		if (data->parser->typefile[i] == DBL_REDIR_IN)
		
		i++;
	}
	return (NULL);
}

int	ft_heredocs(t_mini *data)
{
	int	i;

	i = 0;
	data->nbr_hd = count_hd(data);
	take_delimiter(data);
	while (i < data->nbr_hd)
	{
		ft_printf("nombre d'heredoc === %d\n", data->nbr_hd);
		i++;
	}
	return (0);
}

// ls << lim | << bateau | echo hello | << hello | << lala ls