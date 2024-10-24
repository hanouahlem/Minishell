/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:33:03 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/23 20:06:24 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_export(t_mini *data)
{
	(void)data;
	printf("hello export\n");
	return(0);
}

int	ft_unset(t_mini *data)
{
	(void)data;
	printf("hello unset\n");
	return(0);
}
