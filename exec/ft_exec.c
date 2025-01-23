/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:21:48 by ahbey             #+#    #+#             */
/*   Updated: 2025/01/23 21:10:06 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_ve(t_mini *data, int i)
{
	char	**path;

	path = get_path_exec(data->exec->env_exec);
	data->parser[i].cmd = give_way_cmd(path, data->parser[i].args[0]);
	if (data->parser[i].cmd == NULL)
	{
		free_tab(path);
		free_exec(data, NULL, 127);
	}
	clean_hdoc(data);
	if (execve(data->parser[i].cmd, data->parser[i].args,
			data->exec->env_exec) < 0)
	{
		free_tab(path);
		free_exec(data, NULL, 127);
	}
	free(data->parser[i].cmd);
	free_tab(data->parser[i].args);
}

void	clean_up_exec(t_mini *data)
{
	close(data->exec->pipe_fd[0]);
	free(data->exec->pid);
	free_tab(data->exec->env_exec);
}

int	exec_commands(t_mini *data, t_parse *tab, t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < exec->nbcmd)
	{
		if (exec_pipe(exec) == 1)
			return (free_exec(data, "Fail pid\n", 1), 1);
		exec->pid[i] = fork();
		if (exec->pid[i] == -1)
			return (free_exec(data, "Fail pid\n", 1), 1);
		if (exec->pid[i] == 0)
			exec_child_process(data, exec, tab, i);
		else
			exec_parent_process(exec, i);
	}
	return (0);
}

int	ft_exec(t_mini *data, t_parse *tab)
{
	int		i;
	t_exec	exec;

	i = -1;
	ft_memset(&exec, 0, sizeof(t_exec));
	data->exec = &exec;
	if (ft_heredocs(data) == 1)
		return (1);
	if ((tab->size_cmd == 1 && ft_is_builtin(tab, 0) == 0))
		return (one_cmd(data, tab, 0));
	if (g_sign_return == SIGINT)
		return (1);
	init_exec(data, &exec);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (exec_commands(data, tab, &exec) == 1)
		return (1);
	wait_for_processes(&exec, data);
	return (clean_up_exec(data), 0);
}
