/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_hm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:07:00 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/25 18:22:05 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_everything(t_mini *data, t_parse *tab )
{
	int	i;

	i = 0;
	while (i < tab->size_cmd - 1)
	{
		free(data->exec->pipes[i]);
		i++;
	}
	free(data->exec->pipes);
	free(data->exec->pid);
}
void	ft_exec_ve(t_mini *data)
{
	char	**way;

	way = get_path_exec(data->exec->env_exec);
	data->parser->cmd = give_way_cmd(way, data->parser->args[0]);
	if (!data->parser->cmd)
		return (free_tab(way), free_tab(data->parser->args), exit(1));
	ft_printf("data->parser->args[0] : %s\nway : %s\n", data->parser->args[0], way);
	execve(data->parser->cmd, data->parser->args, data->exec->env_exec);
	free(data->parser->cmd);
	free_tab(data->parser->args);
}

void	close_pipes(t_mini *data, t_parse *tab)
{
	int	i;

	i = 0;
	while (i < tab->size_cmd - 1)
	{
		printf("hello1\n");
		close(data->exec->pipes[i][0]);
		close(data->exec->pipes[i][1]);
		i++;
	}
}

void	env_in_tab(t_mini *data)
{
	t_env *tmp;
	int i;
	int env_size;

	tmp = data->env;
	env_size = 0;
	i = 0;
	if (!data->exec)
	{
		data->exec = malloc(sizeof(t_exec));
		if (!data->exec)
		{
			perror("malloc failed for data->exec");
			return ;
		}
	}
	data->exec->env_exec = NULL;
	while (tmp)
	{
		env_size++;
		tmp = tmp->next;
	}
	if (data->exec->env_exec)
		free(data->exec->env_exec);
	data->exec->env_exec = malloc(sizeof(char *) * (env_size + 1));
	if (!data->exec->env_exec)
	{
		perror("malloc failed for data->exec->env_exec");
		return ;
	}
	tmp = data->env;
	while (tmp)
	{
		data->exec->env_exec[i] = tmp->content;
		// printf("env_exec[i] -> %s\n", data->exec->env_exec[i]);
		i++;
		tmp = tmp->next;
	}
	data->exec->env_exec[i] = NULL;
}

int	child_outfile(t_mini *data, int	i, t_parse *tab)
{
	int	outfile_fd;

	outfile_fd = open(tab->filename[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
	{
		perror(tab->filename[1]);
		return (1);
	}
	dup2(data->exec->pipes[i - 1][0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close_pipes(data, tab);
	ft_exec_ve(data);
	return(0);
}

int	child_infile(t_mini *data, int i, t_parse *tab)
{
	int	infile_fd;

	infile_fd = open(tab->filename[0], O_RDONLY, 0777);
	if (infile_fd == -1)
	{
		perror(tab->filename[0]);
		return (1);
	}
	dup2(infile_fd, STDIN_FILENO);
	dup2(data->exec->pipes[i][1], STDOUT_FILENO);
	close(infile_fd);
	close_pipes(data, tab);
	ft_exec_ve(data);
	return(0);
}

void	child(t_mini *data, int i, t_parse *tab)
{
	dup2(data->exec->pipes[i - 1][0], STDIN_FILENO);
	dup2(data->exec->pipes[i][1], STDOUT_FILENO);
	close_pipes(data, tab);
	ft_exec_ve(data);
}

char **get_path(char **env)
{
    while (*env)
    {
        if (ft_strncmp(*env, "PATH=", 5) == 0)
            return (ft_split(*env + 5, ':'));
        env++;
    }
    return (NULL);
}

int	forking(t_mini *data, int i, t_parse *tab)
{
	data->exec->pid[i] = fork();
	if (data->exec->pid[i] == -1)
	{
		perror("Fork Failed !\n");
		return (EXIT_FAILURE);
	}
	if (data->exec->pid[i] == 0)
	{
		if (i == 0)
			child_infile(data, i, tab);
		else if (i == tab->size_cmd - 1)
			child_outfile(data, i, tab);
		else
			child(data, i, tab);
	}
	return(0);
}

void	init_exec(t_mini *data)
{
	int	i;

	env_in_tab_exec(data);
	data->exec->infile = -1;
	data->exec->outfile = -1;
	data->exec->fd_tmp = -1;
	data->exec->pid = malloc(sizeof(pid_t) * data->parser->size_cmd);
	// Initialisation des pipes (si plus d'une commande)
	i = 0;
	while (i < data->parser->size_cmd - 1)
	{
		data->exec->pipes[i] = malloc(2 * sizeof(int));
		if (pipe(data->exec->pipes[i]) == -1)
		{
			perror("Pipe failed");
			free_resources(data);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	ft_exec_hm(t_mini *data, t_parse *tab)
{
	int	i;

	i = 0;
	init_exec(data);
	printf("size_cmd %d\n", tab->size_cmd);
	while (i < tab->size_cmd - 1)
	{
		if (pipe(data->exec->pipes[i]) == -1)
		{
			perror("Pipe Failed !\n");
			free_everything(data, tab);
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < tab->size_cmd - 1)
	{
		if (forking(data, i, tab) == EXIT_FAILURE)
		{
			free_everything(data, tab);
			return (EXIT_FAILURE);
		}
		i++;
	}
	close_pipes(data, tab);
	i = 0;
	while (i < tab->size_cmd - 1)
	{
		waitpid(*data->exec->pipes[i], NULL, 0);
		i++;
	}
	// if(data || tab)
	// 	free_everything(data, tab);
	return (0);
}
