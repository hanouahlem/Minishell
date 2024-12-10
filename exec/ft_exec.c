/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:21:48 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/10 18:23:12 by ahbey            ###   ########.fr       */
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

void	free_exec(t_mini *data, char *str, int valuexit) // int pour exit
{
	ft_printf("%s", str);
	close_standard(data->standard);
	free_inside(data, NULL, data->parser);
	free_env(data);
	free_tab(data->exec->env_exec);
	free(data->exec->pid);
	exit(valuexit);
}

void	ft_exec_ve(t_mini *data, int i)
{
	char	**path;

	path = get_path_exec(data->exec->env_exec);
	printf("args ----------> %s\n", data->parser[i].args[0]);
	data->parser[i].cmd = give_way_cmd(path, data->parser[i].args[0]);
	if (data->parser[i].cmd == NULL)
	{
		free_tab(path);
		free_exec(data, "No such file or directory\n", 127);
		// free_exec(data, NULL);
		exit(1);
	}
	fprintf(stderr,"parser[i] = %s\n", data->parser[i].cmd);
	fprintf(stderr, "tab = %s\n", data->parser[i].args[0]);
	if (execve(data->parser[i].cmd, data->parser[i].args, data->exec->env_exec) < 0)
	{
		ft_printf("Excve Fail !\n");
		free_tab(path);
		free_exec(data, NULL, 127);
	}
	free(data->parser[i].cmd);
	free_tab(data->parser[i].args);
}

void	redirections_pipe(t_exec *exec, int index)
{
	if (index != 0) // lire
	{
		dup2(exec->pipe_prev, STDIN_FILENO);
		close(exec->pipe_prev);
	}
	if (index != exec->nbcmd - 1) // ecrire
	{
		dup2(exec->pipe_fd[1], STDOUT_FILENO);
	}
	close(exec->pipe_fd[0]);
	close(exec->pipe_fd[1]);
}

void	init_exec(t_mini *data, t_exec *exec)
{
	env_in_tab_exec(data);
	exec->nbcmd = data->parser->size_cmd;
	exec->pid = ft_calloc(sizeof(int), exec->nbcmd);
	exec->pipe_prev = -1;
}

int	redirection_fichier(t_mini *data, t_parse *tab)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (i < tab->filename_count)
	{
		if (tab->typefile[i] == REDIR_OUT)
			fd = open(tab->filename[i], O_WRONLY | O_TRUNC | O_CREAT, 0664);
		else if (tab->typefile[i] == DBL_REDIR_OUT)
			fd = open(tab->filename[i], O_WRONLY | O_APPEND | O_CREAT, 0664);
		else if (tab->typefile[i] == REDIR_IN)
			fd = open(tab->filename[i], O_RDONLY);
		// else if (tab->typefile[i] == DBL_REDIR_IN)
		// 	ft_heredocs(data);
		if (fd == -1)
		{
			free_exec(data, "Open Fail \n", 1);
		}
		if (tab->typefile[i] == REDIR_OUT || tab->typefile[i] == DBL_REDIR_OUT)
			dup2(fd, STDOUT_FILENO);
		else if (tab->typefile[i] == REDIR_IN)
			dup2(fd, STDIN_FILENO);
		close(fd);
		i++;
	}
	return (0);
}

int	worst_builtin(t_parse *tab)
{
	if (ft_strcmp(tab->args[0], "unset") == 0)
		return (0);
	if (ft_strcmp(tab->args[0], "export") == 0)
		return (0);
	if (ft_strcmp(tab->args[0], "exit") == 0)
		return (0);
	if (ft_strcmp(tab->args[0], "cd") == 0)
		return (0);
	if (ft_strcmp(tab->args[0], "pwd") == 0)
		return (0);
	return (1);
}

int	one_cmd(t_mini *data, t_parse *tab, int i)
{
	data->standard[0] = dup(0);
	data->standard[1] = dup(1);
	if (data->standard[0] == -1 || data->standard[1] == -1)
	{
		perror("dup");
		return (-1);
	}
	redirection_fichier(data, &tab[i]);
	data->exit_status = ft_built_in_comp(data, tab, i);
	if (dup2(data->standard[0], 0) == -1 || dup2(data->standard[1], 1) == -1)
	{
		perror("dup2");
		return (-1);
	}
	close(data->standard[0]);
	close(data->standard[1]);
	data->standard[0] = -1;
	data->standard[1] = -1;
	return (0);
}

int	ft_exec(t_mini *data, t_parse *tab)
{
	int		i;
	t_exec	exec;

	i = 0;
	ft_memset(&exec, 0, sizeof(t_exec));
	data->exec = &exec;
	ft_heredocs(data);
	if (tab->size_cmd == 1 && ft_is_builtin(tab, 0) == 0)
	{
		one_cmd(data, tab, i);
		return (1);
	}
	init_exec(data, &exec);
	while (i < exec.nbcmd)
	{
		if (pipe(exec.pipe_fd) == -1)
			return (printf("Error: pipe fail\n"), 1);
		exec.pid[i] = fork();
		if (exec.pid[i] == -1)
			free_exec(data, "Fail pid\n", 1);
		if (exec.pid[i] == 0) // enfant
		{
			redirections_pipe(&exec, i);
			redirection_fichier(data, &tab[i]);
			if (ft_is_builtin(tab, i) == 1)
				ft_exec_ve(data, i);
			else
				ft_built_in_comp(data, tab, i);
			free_exec(data, NULL, 127);
		}
		else // parent
		{
			if (i > 0)
				close(exec.pipe_prev);
			exec.pipe_prev = exec.pipe_fd[0];
			close(exec.pipe_fd[1]);
		}
		data->exit_status = 0;
		i++;
	}
	i = 0;
	while (i < exec.nbcmd)
	{
		waitpid(exec.pid[i++], &data->exit_status, 0);
		if (WIFEXITED(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
	}
	close(data->exec->pipe_fd[0]);
	free(data->exec->pid);
	free_tab(data->exec->env_exec);
	return (0);
}