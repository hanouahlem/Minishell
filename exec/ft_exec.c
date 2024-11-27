/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:21:48 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/27 15:13:54 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_mini *data, char *str)
{
	ft_printf("%s", str);
	free_inside(data, NULL, data->parser);
	free_env(data);
	if (data->exec->env_exec)
		free(data->exec->env_exec);
	if (data->exec->pid)
		free(data->exec->pid);
	exit(1);
}

void	ft_exec_ve(t_mini *data, int i)
{
	char	**path;

	path = get_path_exec(data->exec->env_exec);
	data->parser[i].cmd = give_way_cmd(path, data->parser[i].args[0]);
	if (data->parser[i].cmd == NULL)
	{
		free_tab(path);
		free_exec(data, NULL);
	}
	execve(data->parser[i].cmd, data->parser[i].args, data->exec->env_exec);
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
	exec->pid = malloc(sizeof(int) * exec->nbcmd);
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
		if (tab->typefile[i] == DBL_REDIR_OUT)
			fd = open(tab->filename[i], O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (tab->typefile[i] == REDIR_IN)
			fd = open(tab->filename[i], O_RDONLY);
		if (tab->typefile[i] == DBL_REDIR_IN)
			;//heredoc
		if (fd == -1)
		{
			free_exec(data, "Open Fail \n");
		}
		// if fd == -1
		// exit error
		if (tab->typefile[i] == REDIR_OUT || tab->typefile[i] == DBL_REDIR_OUT)
			dup2(fd, STDOUT_FILENO);
		else
			dup2(fd, STDIN_FILENO);
		close(fd);
		i++;
	}
	return (0);
}

int	ft_exec(t_mini *data, t_parse *tab)
{
	int		i;
	t_exec	exec;

	i = 0;
	(void)tab;
	data->exec = &exec;
	init_exec(data, &exec);
	while (i < exec.nbcmd)
	{
		pipe(exec.pipe_fd);
		exec.pid[i] = fork();
		if (exec.pid[i] == -1)
		{
			// error // free
			free_exec(data, "Fail pid\n");
			exit(1);
		}
		if (exec.pid[i] == 0) // enfant
		{
			redirections_pipe(&exec, i);
			redirection_fichier(data, &tab[i]);
			// si commande NEST PAS UN BUILTIN
			if (ft_is_builtin(tab) == 1)
				ft_exec_ve(data, i);
			else if(ft_is_builtin(tab) == 0 && tab->size_cmd > 1)// il rentre dedans que si il ya plus d'une commande
			{
				ft_printf("HELLO WORLD\n");
				ft_built_in_comp(data, tab);
			}
			free_exec(data, NULL);
			exit(127);
		}
		else // parent
		{
			if (i > 0)
				close(exec.pipe_prev);
			exec.pipe_prev = exec.pipe_fd[0];
			close(exec.pipe_fd[1]);
		}
		i++;
	}
	i = 0;
	while (i < exec.nbcmd)
		waitpid(exec.pid[i++], NULL, 0);
	close(data->exec->pipe_fd[0]);
	free(data->exec->pid);
	free(data->exec->env_exec);
	return (0);
}
