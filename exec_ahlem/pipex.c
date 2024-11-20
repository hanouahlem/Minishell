/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:32:33 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/19 19:47:01 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_init(t_pipe *pex, int ac, char **av, char **env)
{
	int	i;

	pex->infile = av[1];
	pex->outfile = av[ac - 1];
	pex->cmds = &av[2];      // Commandes entre infile et outfile
	pex->cmd_count = ac - 4; // Nombre de commandes (sans infile et outfile)
	pex->env = env;
	// Allouer de la mémoire pour les pipes et les PIDs
	pex->pipes = malloc((pex->cmd_count - 1) * sizeof(int *));
	i = 0;
	while (i < pex->cmd_count - 1)
	{
		pex->pipes[i] = malloc(2 * sizeof(int));
		i++;
	}
	pex->pid = malloc(pex->cmd_count * sizeof(pid_t));
}

int	main(int ac, char **av, char **env)
{
	static t_pipe	pex = {0};
	int				i;

	make_init(&pex, ac, av, env);
	i = 0;
	while (i < pex.cmd_count)
	{
		if (pipe(pex.pipes[i]) == -1)
		{
			perror("Pipe failed");
			free_resources(&pex);
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < pex.cmd_count)
	{
		if (forking(&pex, i) == EXIT_FAILURE)
		{
			free_resources(&pex);
			return (EXIT_FAILURE);
		}
		i++;
	}
	close_all_pipes(&pex);
	i = 0;
	while (i < pex.cmd_count)
	{
		waitpid(pex.pid[i], NULL, 0);
		i++;
	}
	free_resources(&pex);
	return (0);
}
