/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:21:48 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/30 22:58:33 by ahbey            ###   ########.fr       */
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

int	one_cmd(t_mini *data, t_parse *tab, int i)
{
	data->standard[0] = dup(0);
	data->standard[1] = dup(1);
	if (data->standard[0] == -1 || data->standard[1] == -1)
	{
		perror("dup");
		return (1);
	}
	redirection_fichier(data, &tab[i]);
	data->exit_status = ft_built_in_comp(data, tab, i);
	if (dup2(data->standard[0], 0) == -1 || dup2(data->standard[1], 1) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(data->standard[0]);
	close(data->standard[1]);
	data->standard[0] = -1;
	data->standard[1] = -1;
	return (0);
}

void	make_child(t_mini *data, t_parse *tab, t_exec *exec, int i)
{
	if (exec->pid[i] == 0) // enfant
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
		{
			ft_built_in_comp(data, tab, i);
		}
		free_exec(data, NULL, 127);
	}
	else // parent
	{
		if (i > 0)
			close(exec->pipe_prev);
		exec->pipe_prev = exec->pipe_fd[0];
		close(exec->pipe_fd[1]);
	}
}

void	ft_waitpid_exec(t_mini *data, t_exec *exec, int *i)
{
	while (*i < exec->nbcmd)
	{
		waitpid(exec->pid[(*i)++], &data->exit_status, 0);
		if (WIFEXITED(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
	}
}

int	ft_exec(t_mini *data, t_parse *tab)
{
	int		i;
	t_exec	exec;

	i = 0;
	ft_memset(&exec, 0, sizeof(t_exec));
	data->exec = &exec;
	if (before_exec(data, tab, &exec, i) == 1)
		return (1);
	while (i < exec.nbcmd)
	{
		if (pipe(exec.pipe_fd) == -1)
			return (printf("Error: pipe fail\n"), 1);
		exec.pid[i] = fork();
		if (exec.pid[i] == -1)
			free_exec(data, "Fail pid\n", 1);
		make_child(data, tab, &exec, i);
		data->exit_status = 0;
		i++;
	}
	i = 0;
	ft_waitpid_exec(data, &exec, &i); // Appel à la nouvelle fonction
	close(data->exec->pipe_fd[0]);
	free(data->exec->pid);
	free_tab(data->exec->env_exec);
	return (0);
}
