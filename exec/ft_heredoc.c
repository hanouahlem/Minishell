/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:21:43 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/12 18:28:55 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_hd(t_mini *data)
{
	size_t	i;
	t_token	*tmp;

	i = 0;
	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == DBL_REDIR_IN)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	take_delimiter(t_mini *data, t_hdoc *hdoc)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == DBL_REDIR_IN)
		{
			hdoc[i].delim = tmp->next->value_t;
			// ft_printf("delim ==> %s\n",hdoc[i].delim);
			

			
			if (pipe(hdoc[i].pipe_fd) == -1)
			{
				perror("pipe");
				exit(1);
			}
			i++;
		}
		tmp = tmp->next;
		if (i >= data->nbr_hd)
			break ;
	}
}

void	write_hd(t_hdoc *hdoc, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, hdoc->delim))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);

}

void	exec_heredoc(t_mini *data, t_hdoc *hdoc, int *i)
{
	while (*i < data->nbr_hd)
	{
		close(hdoc[*i].pipe_fd[0]);
		write_hd(hdoc, hdoc[*i].pipe_fd[1]);
		free(hdoc[*i].delim);
		(*i)++;
	}
	free(hdoc);
	exit(0);
}

void	clean_hdoc(t_mini *data)
{
	free_inside(data, NULL, data->parser);
	
}

int	ft_heredocs(t_mini *data)
{
	int		i;
	t_hdoc	*hdoc;
	int		pid;

	i = 0;
	data->nbr_hd = count_hd(data);
	if(!data->nbr_hd)
		return(0);
	hdoc = ft_calloc(sizeof(t_hdoc), (data->nbr_hd));
	if (!hdoc)
		return (1);
	take_delimiter(data, hdoc);
	pid = fork();
	if (pid == 0)
		exec_heredoc(data, hdoc, &i);
	else if (pid > 0)
	{
		i = 0;
		while (i < data->nbr_hd)
			close(hdoc[i++].pipe_fd[1]);
		waitpid(pid, 0, 0);
	}
	i = 0;
	while (i < data->nbr_hd)
	{
		close(hdoc[i].pipe_fd[0]);
		close(hdoc[i].pipe_fd[1]);
		i++;
	}
	// clean_hdoc(data, data->nbr_hd);
	return (0);
}

// ls << lim | << bateau | echo hello | << hello | << lala ls