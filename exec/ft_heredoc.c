/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:21:43 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/27 19:14:01 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t count_hd(t_mini *data)
{
	size_t i;
	t_token *tmp;

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

int write_hd(t_mini *data, t_hdoc *hdoc, int fd, int i)
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (sign_return != 0)
		{
			data->exit_status = sign_return;
			sign_return = 0;
			return (1);
		}
		if (!line)
		{
			ft_printf("mini: warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", hdoc[i].delim);
			return (0);
		}
		if (!ft_strcmp(line, hdoc[i].delim))
		{
			return (close(fd), free(line), 0);
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);

	return (0);
}

int take_delimiter(t_mini *data, t_hdoc *hdoc)
{
	int i;
	t_token *tmp;

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
			if (write_hd(data, hdoc, hdoc[i].pipe_fd[1], i) == 1)
			{
				dprintf(2, "apres le write hd\n");
				return (1);
			}
			i++;
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
		if (i >= data->nbr_hd)
			return (0);
	}
	return (0);
}

void signal_here_doc(int signum)
{
	if (signum == SIGINT)
		sign_return = SIGINT;
	rl_replace_line("", 0); // Efface la ligne courante
	rl_on_new_line();		// Signale une nouvelle ligne
	rl_redisplay();
}

int ft_heredocs(t_mini *data)
{
	int i;
	t_hdoc *hdoc;
	t_token *tmp;

	i = 0;
	tmp = data->token;
	data->nbr_hd = count_hd(data);
	if (data->nbr_hd == 0)
		return (0);
	hdoc = ft_calloc(sizeof(t_hdoc), (data->nbr_hd + 1));
	if (!hdoc)
		return (1);
	if (take_delimiter(data, hdoc) == 1)
	{
		data->heredoc = hdoc;
		return (1);
	}
	data->heredoc = hdoc;
	if (sign_return == SIGINT)
	{
		data->check = 1;
		data->exit_status = 130;
	}
	return (0);
}
