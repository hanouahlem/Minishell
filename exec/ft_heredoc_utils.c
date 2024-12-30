/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 21:59:16 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/30 22:58:34 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_hd(t_mini *data, char *str)
{
	int	i;

	i = 0;
	while (i < data->nbr_hd)
	{
		if (!strcmp(data->heredoc[i].delim, str))
			return (data->heredoc[i].pipe_fd[0]);
		i++;
	}
	return (-1);
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

int	before_exec(t_mini *data, t_parse *tab, t_exec *exec, int i)
{
	if (ft_heredocs(data) == 1)
		return (1);
	if (tab->size_cmd == 1 && ft_is_builtin(tab, 0) == 0)
	{
		one_cmd(data, tab, i);
		return (1);
	}
	if (sign_return == SIGINT)
		return (1);
	init_exec(data, exec);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

void	init_exec(t_mini *data, t_exec *exec)
{
	env_in_tab_exec(data);
	exec->nbcmd = data->parser->size_cmd;
	exec->pid = ft_calloc(sizeof(int), exec->nbcmd);
	exec->pipe_prev = -1;
}
