/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:21:43 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/23 16:34:46 by ahbey            ###   ########.fr       */
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

void	write_hd(t_mini *data, t_hdoc *hdoc, int fd, int i)
{
	char	*line;

	(void)data;
	while (1)
	{
		line = readline("> ");
		if (!line && sign_return != SIGINT)
		{
			ft_printf("mini: warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", hdoc[i].delim);
			break ;
		}
		if (sign_return == SIGINT)
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
			write_hd(data, hdoc, hdoc[i].pipe_fd[1], i);
			i++;
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
		if (i >= data->nbr_hd)
			break;
	}
}

void clean_heredoc(t_mini *data) {
    int i = 0;
    while (i < data->nbr_hd) {
        if (data->heredoc[i].delim) {
            free(data->heredoc[i].delim);
            data->heredoc[i].delim = NULL;
        }
        close(data->heredoc[i].pipe_fd[0]);
        close(data->heredoc[i].pipe_fd[1]);
        i++;
    }
    free(data->heredoc);
    data->heredoc = NULL;
}

void	signal_here_doc(int signum)
{
	if (signum == SIGINT)
		sign_return = SIGINT;
	close (STDIN_FILENO);
	printf("\n");
}

int	ft_heredocs(t_mini *data)
{
	int	i;
	t_hdoc	*hdoc;
	t_token	*tmp;
	int	std;

	std = dup(0);
	i = 0;
	tmp = data->token;
	data->nbr_hd = count_hd(data);
	if (data->nbr_hd == 0)
	{
		close(std);
		return (1);
	}
	hdoc = ft_calloc(sizeof(t_hdoc), (data->nbr_hd + 1));
	if (!hdoc)
	{
		close(std);
		return (1);
	}
	signal(SIGINT, signal_here_doc);
	take_delimiter(data, hdoc);
	data->heredoc = hdoc;
	if (sign_return == SIGINT)
	{
		data->check = 1;
		dup2(std, STDIN_FILENO);
		data->exit_status = 130;
	}
	close(std);
	return (0);
}

// ls << lim | << bateau | echo hello | << hello | << lala ls