/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:55:02 by manbengh          #+#    #+#             */
/*   Updated: 2025/01/23 21:26:40 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (1);
}

void	init_exec(t_mini *data, t_exec *exec)
{
	env_in_tab_exec(data);
	exec->nbcmd = data->parser->size_cmd;
	exec->pid = ft_calloc(sizeof(int), exec->nbcmd);
	exec->pipe_prev = -1;
}

void	redirections_pipe(t_exec *exec, int index)
{
	if (index != 0)
	{
		dup2(exec->pipe_prev, STDIN_FILENO);
		close(exec->pipe_prev);
	}
	if (index != exec->nbcmd - 1)
	{
		dup2(exec->pipe_fd[1], STDOUT_FILENO);
	}
	close(exec->pipe_fd[0]);
	close(exec->pipe_fd[1]);
}

void	if_is_redir_file(t_mini *data, t_parse *tab, int *i, int *fd)
{
	if (tab->typefile[*i] == REDIR_OUT)
		*fd = open(tab->filename[*i], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	else if (tab->typefile[*i] == DBL_REDIR_OUT)
		*fd = open(tab->filename[*i], O_WRONLY | O_APPEND | O_CREAT, 0664);
	else if (tab->typefile[*i] == REDIR_IN)
		*fd = open(tab->filename[*i], O_RDONLY);
	else if (tab->typefile[*i] == DBL_REDIR_IN)
		*fd = find_hd(data, tab->filename[*i]);
	if (*fd == -1)
	{
		if (access(tab->filename[*i], F_OK))
			ft_printf("Error : %s : No such file or directory\n",
				tab->filename[*i]);
		else
			ft_printf("Error : %s : Permission denied\n", tab->filename[*i]);
		free_exec(data, NULL, 1);
	}
}

int	redirection_fichier(t_mini *data, t_parse *tab)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (i < tab->filename_count)
	{
		if_is_redir_file(data, tab, &i, &fd);
		if (tab->typefile[i] == REDIR_OUT || tab->typefile[i] == DBL_REDIR_OUT)
			dup2(fd, STDOUT_FILENO);
		else if (tab->typefile[i] == REDIR_IN
			|| tab->typefile[i] == DBL_REDIR_IN)
			dup2(fd, STDIN_FILENO);
		i++;
		if (tab->typefile[i] != DBL_REDIR_IN)
			close(fd);
	}
	return (0);
}
