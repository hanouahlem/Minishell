/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:32:42 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/19 18:56:06 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_resources(t_pipe *pex)
{
	int	i;

	i = 0;
	while (i < pex->cmd_count - 1)
	{
		free(pex->pipes[i]);
		i++;
	}
	free(pex->pipes);
	free(pex->pid);
}

void free_tab(char **str)
{
    int i = 0;
    while (str && str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}
