/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 21:58:21 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/30 21:52:19 by ahbey            ###   ########.fr       */
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

void	free_exec(t_mini *data, char *str, int valuexit)
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
				ft_printf("Error : %s : No such file or directory\n",
					tab->filename[i]);
			else
				ft_printf("Error : %s : Permission denied\n", tab->filename[i]);
			free_exec(data, NULL, 1);
		}
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