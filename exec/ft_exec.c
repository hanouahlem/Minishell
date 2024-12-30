/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:21:48 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/30 17:19:30 by manbengh         ###   ########.fr       */
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

int	ft_exec(t_mini *data, t_parse *tab)
{
	int		i;
	t_exec	exec;

	i = -1;
	ft_memset(&exec, 0, sizeof(t_exec));
	data->exec = &exec;
	if (ft_heredocs(data) || (tab->size_cmd == 1 && ft_is_builtin(tab, 0) == 0))
		return (one_cmd(data, tab, 0));
	if (sign_return == SIGINT)
		return (1);
	init_exec(data, &exec);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (++i < exec.nbcmd)
	{
		ft_printf("i -----> %i\n", i);
		exec.pid[i] = fork();
		if (exec_pipe(&exec) || exec.pid[i] == -1)
			return (free_exec(data, "Fail pid\n", 1), 1);
		if (exec.pid[i] == 0)
			exec_child_process(data, &exec, tab, i);
		else
			exec_parent_process(&exec, i);
	}
	wait_for_processes(&exec, data);
	return (clean_up_exec(data), 0);
}
