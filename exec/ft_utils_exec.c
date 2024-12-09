/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:22:28 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/07 19:43:29 by ahbey            ###   ########.fr       */
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

int	ft_heredocs(t_mini *data)
{
	int i;

	i = 0 ;
	data->nbr_hd = count_hd(data);
	while(i < data->nbr_hd)
	{
		ft_printf("nombre d'heredoc === %d\n", data->nbr_hd);
		i++;
	}
	return (0);
}

// ls << lim | << bateau | << hello | << lala