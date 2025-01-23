/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:02:07 by manbengh          #+#    #+#             */
/*   Updated: 2024/12/30 17:02:10 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_standard(int standard[2])
{
	if (standard[0] != -1)
		close(standard[0]);
	if (standard[1] != -1)
		close(standard[1]);
}

void	clean_hdoc(t_mini *data)
{
	int	i;

	i = 0;
	if (!data->heredoc)
		return ;
	while (i < data->nbr_hd)
	{
		if (data->heredoc[i].delim)
			free(data->heredoc[i].delim);
		if (data->heredoc[i].pipe_fd[0] > 2)
			close(data->heredoc[i].pipe_fd[0]);
		if (data->heredoc[i].pipe_fd[1] > 2)
			close(data->heredoc[i].pipe_fd[1]);
		i++;
	}
	if (data->nbr_hd != 0)
		free(data->heredoc);
}

void	free_exec(t_mini *data, char *str, int valuexit)
{
	ft_printf("%s", str);
	close_standard(data->standard);
	clean_hdoc(data);
	free_inside(data, NULL, data->parser);
	free_env(data);
	free_tab(data->exec->env_exec);
	free(data->exec->pid);
	exit(valuexit);
}
