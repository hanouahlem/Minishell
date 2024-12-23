/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:21:48 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/14 19:09:44 by ahbey            ###   ########.fr       */
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
		return;
	while (i < data->nbr_hd)
	{
		if (data->heredoc[i].delim)
			free(data->heredoc[i].delim);
		if (data->heredoc[i].pipe_fd[0] >= 0)
			close(data->heredoc[i].pipe_fd[0]);
		i++;
	}
	if (data->heredoc)
		free(data->heredoc);
}

void	free_exec(t_mini *data, char *str, int valuexit) // int pour exit
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

void	ft_exec_ve(t_mini *data, int i)
{
	char	**path;

	path = get_path_exec(data->exec->env_exec);
	data->parser[i].cmd = give_way_cmd(path, data->parser[i].args[0]);
	if (data->parser[i].cmd == NULL)
	{
		free_tab(path);
		free_exec(data, "Error : Command not found\n", 127);
	}
	clean_hdoc(data);
	if (execve(data->parser[i].cmd, data->parser[i].args, data->exec->env_exec) < 0)
	{
		free_tab(path);
		free_exec(data, "Error : Command not found\n", 127);
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

int find_hd(t_mini *data, char *str)
{

	int i = 0;
	while(i < data->nbr_hd)
	{
		if (!strcmp(data->heredoc[i].delim, str))
			return (data->heredoc[i].pipe_fd[0]);
		i++;
	}
	return (-1);
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
		else if (tab->typefile[i] == DBL_REDIR_IN)
			fd = find_hd(data, tab->filename[i]);
		if (fd == -1)
		{	
			if (access(tab->filename[i], F_OK))
				ft_printf("Error : %s : No such file or directory\n",tab->filename[i] );
			else
				ft_printf("Error : %s : Permission denied\n", tab->filename[i]);
			free_exec(data, NULL, 1);
		}
		if (tab->typefile[i] == REDIR_OUT || tab->typefile[i] == DBL_REDIR_OUT)
			dup2(fd, STDOUT_FILENO);
		else if (tab->typefile[i] == REDIR_IN || tab->typefile[i] == DBL_REDIR_IN)
			dup2(fd, STDIN_FILENO);
		i++;
		if (tab->typefile[i] != DBL_REDIR_IN)
			close(fd);
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


void	signal_pipex(int signum)
{
	if (signum == SIGQUIT)
		sign_return = SIGQUIT;
	else
		sign_return = SIGINT;
	ft_printf("signal recu pipex\n");
}

// void	signal_here_doc(int signum)
// {
// 	if (signum == SIGINT)
// 		sign_return = SIGINT;
// 	printf("signal recu depuis heredoc\n");
// 	close (STDIN_FILENO);
// }

int	ft_exec(t_mini *data, t_parse *tab)
{
	int		i;
	t_exec	exec;
	// int		std = dup(0);

	i = 0;
	ft_memset(&exec, 0, sizeof(t_exec));
	data->exec = &exec;
	// signal(SIGINT, signal_here_doc);
	ft_heredocs(data);
	// if (sign_return == SIGINT)
	// {
	// 	dup2(std, STDIN_FILENO);
	// 	data->exit_status = 130;
	// }
	// close(std);
	if (tab->size_cmd == 1 && ft_is_builtin(tab, 0) == 0)
	{
		one_cmd(data, tab, i);
		return (1);
	}
	if (sign_return == SIGINT)
		return (1);
	// disable_signals();
	init_exec(data, &exec);
	signal(SIGINT, SIG_IGN);
	while (i < exec.nbcmd)
	{
		if (pipe(exec.pipe_fd) == -1)
			return (printf("Error: pipe fail\n"), 1);
		exec.pid[i] = fork();
		if (exec.pid[i] == -1)
			free_exec(data, "Fail pid\n", 1);
		if (exec.pid[i] == 0) // enfant
		{
			// disable_signals();
			signal(SIGQUIT, signal_pipex);
			signal(SIGINT, signal_pipex);
			redirections_pipe(&exec, i);
			redirection_fichier(data, &tab[i]);
			if(!tab->args || !tab->args[0])
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
		// sign_return = 131;
	}
	close(data->exec->pipe_fd[0]);
	free(data->exec->pid);
	free_tab(data->exec->env_exec);
	return (0);
}
