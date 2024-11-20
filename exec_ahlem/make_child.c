/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:33:37 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/19 19:29:32 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	forking(t_pipe *pex, int i)
{
	pex->pid[i] = fork();
	if (pex->pid[i] == -1)
	{
		perror("Fork failed");
		return (EXIT_FAILURE);
	}
	if (pex->pid[i] == 0)
	{
		if (i == 0)
			child_infile(pex, i);
		else if (i == pex->cmd_count - 1)
			child_outfile(pex, i);
		else
			child_intermediate(pex, i);
	}
	return (0);
}

void	close_all_pipes(t_pipe *pex)
{
	int	i;

	i = 0;
	while (i < pex->cmd_count - 1)
	{
		close(pex->pipes[i][0]);
		close(pex->pipes[i][1]);
		i++;
	}
}
void	child_infile(t_pipe *pex, int i)
{
	int	infile_fd;

	infile_fd = open(pex->infile, O_RDONLY);
	if (infile_fd == -1)
	{
		perror(pex->infile);
		exit(EXIT_FAILURE);
	}
	dup2(infile_fd, STDIN_FILENO);
	dup2(pex->pipes[i][1], STDOUT_FILENO);
	close(infile_fd);
	close_all_pipes(pex);
	exec_ve(pex->cmds[i], pex->env);
}

void	child_outfile(t_pipe *pex, int i)
{
	int	outfile_fd;

	outfile_fd = open(pex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
	{
		perror(pex->outfile);
		exit(EXIT_FAILURE);
	}
	dup2(pex->pipes[i - 1][0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close_all_pipes(pex);
	exec_ve(pex->cmds[i], pex->env);
}

void	child_intermediate(t_pipe *pex, int i)
{
	dup2(pex->pipes[i - 1][0], STDIN_FILENO);
	dup2(pex->pipes[i][1], STDOUT_FILENO);
	close_all_pipes(pex);
	exec_ve(pex->cmds[i], pex->env);
}
