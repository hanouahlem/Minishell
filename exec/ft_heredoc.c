/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:21:43 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/14 19:12:34 by ahbey            ###   ########.fr       */
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

// void	exec_heredoc(t_mini *data, t_hdoc *hdoc)
// {
// 	int	i = 0;

// 	while (i < data->nbr_hd)
// 	{
// 		close(hdoc[i].pipe_fd[0]);
// 		write_hd(hdoc, hdoc[i].pipe_fd[1]);
// 		free(hdoc[i].delim);
// 		(i)++;
// 	}
// 	free(hdoc);
// }

void	write_hd(t_hdoc *hdoc, int fd, int i)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if(!ft_strcmp(line, hdoc[i].delim))
		{
			free(line);
			break;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

void	take_delimiter(t_mini *data, t_hdoc *hdoc)
{
	int	i;
	t_token	*tmp;
	
	i = 0;
	tmp = data->token;
	ft_printf("ICI\n");
	while (tmp)
	{
		if (tmp->type == DBL_REDIR_IN)
		{
			hdoc[i].delim = ft_strdup(tmp->next->value_t);
			if (!hdoc[i].delim)
				ft_printf("error strdup delim\n");
			if (pipe(hdoc[i].pipe_fd) == -1)
			{
				perror("pipe");
				exit(1);
			}
			write_hd(hdoc, hdoc[i].pipe_fd[1], i);
			i++;
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
		if (i >= data->nbr_hd)
			break;
	}
}

int	ft_heredocs(t_mini *data)
{
	int	i;
	t_hdoc	*hdoc;
	t_token	*tmp;
	
	i = 0;
	tmp = data->token;
	data->nbr_hd = count_hd(data);
	if (data->nbr_hd == 0)
		return (0);
	hdoc = ft_calloc(sizeof(t_hdoc), (data->nbr_hd + 1));
	if (!hdoc)
		return (1);
	take_delimiter(data, hdoc);
	data->heredoc = hdoc;
	return (0);
}

	//virer les fork
	// pid = fork();
	// if (pid == 0)
	// 	exec_heredoc(data, hdoc, &i);
	// else if (pid > 0)
	// {
	// 	i = 0;
	// 	while (i < data->nbr_hd)
	// 		close(hdoc[i++].pipe_fd[1]);
	// 	waitpid(pid, 0, 0);
	// }
// ls << lim | << bateau | echo hello | << hello | << lala ls