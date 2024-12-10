/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:21:43 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/10 18:44:42 by ahbey            ###   ########.fr       */
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
	int	i;
	t_token	*tmp;
	// char *str;
	
	i = 0;
	tmp = data->token;
	while (i < data->nbr_hd)
	{
		if (tmp->type == DBL_REDIR_IN)
		{
			hdoc[i].delim = tmp->next->value_t;
			pipe(hdoc[i].pipe_fd);
			i++;
		}
		tmp = tmp->next;
	}
}

void	exec_heredoc(t_mini *data, t_hdoc *hdoc, int i)
{
	
}

int	ft_heredocs(t_mini *data)
{
	int	i;
	// char *delim;
	t_hdoc	*hdoc;
	char *line;
	int pid;
	
	i = 0;
	data->nbr_hd = count_hd(data);
	hdoc = ft_calloc(sizeof(t_hdoc), (data->nbr_hd + 1));
	if (!hdoc)
		return (0);
	take_delimiter(data, hdoc); 
	while (i < data->nbr_hd)
	{
		pid = fork();
		if (pid == 0)
			exec_heredoc(data, hdoc, &i);
		i++;
		line = readline("> ");
		if (!line)
			break ;
	}
	return (0);
}

// ls << lim | << bateau | echo hello | << hello | << lala ls