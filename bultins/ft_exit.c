/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:36:48 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/06 18:01:57 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_mini *data, t_parse *tab)
{
	(void)data;
	if (data->env)
		free_env(data);
	if (tab)
		free_parser(data, tab);
	if (data->token)
		free_token(data);
	exit(1);
	return (0);
}
