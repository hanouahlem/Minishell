/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:44:52 by manbengh          #+#    #+#             */
/*   Updated: 2024/12/31 20:15:10 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_processes(t_exec *exec, t_mini *data)
{
	int	i;

	i = 0;
	while (i < exec->nbcmd)
	{
		waitpid(exec->pid[i], &data->exit_status, 0);
		if (WIFEXITED(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
		else if (WIFSIGNALED(data->exit_status)
			&& WTERMSIG(data->exit_status) == SIGQUIT)
		{
			ft_printf("Quit (core dumped)\n");
			g_sign_return = 131;
		}
		i++;
	}
}

void	exec_parent_process(t_exec *exec, int i)
{
	if (i > 0)
		close(exec->pipe_prev);
	exec->pipe_prev = exec->pipe_fd[0];
	close(exec->pipe_fd[1]);
}

void	exec_child_process(t_mini *data, t_exec *exec, t_parse *tab, int i)
{
	signal(SIGQUIT, signal_pipex);
	signal(SIGINT, signal_pipex);
	redirections_pipe(exec, i);
	redirection_fichier(data, &tab[i]);
	if (!tab->args || !tab->args[0])
		free_exec(data, NULL, 1);
	if (ft_is_builtin(tab, i) == 1)
		ft_exec_ve(data, i);
	else
		ft_built_in_comp(data, tab, i);
	free_exec(data, NULL, 127);
}

int	exec_pipe(t_exec *exec)
{
	if (pipe(exec->pipe_fd) == -1)
	{
		printf("Error: pipe fail\n");
		return (1);
	}
	return (0);
}
