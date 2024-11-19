/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organise_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:36:41 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/14 18:34:06 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_nbr(t_mini data)
{
	int	i;

	i = 0;
	while (data.token)
	{
		if (data.token->type == PIPE)
			i++;
		data.token = data.token->next;
	}
	i++;
	return (i);
}

int	if_is_redir(int type)
{
	if (type == REDIR_IN || type == REDIR_OUT || type == DBL_REDIR_IN
		|| type == DBL_REDIR_OUT)
		return (0);
	return (1);
}

void	ft_count_elements(t_mini *data, t_parse *tab)
{
	t_token	*token;

	token = data->token;
	tab->args_count = 0;
	tab->typefile_count = 0;
	tab->filename_count = 0;
	while (token && token->type != PIPE)
	{
		if (if_is_redir(token->type) == 0)
		{
			tab->typefile_count++;
			if (token->next && token->next->type == WORD)
				tab->filename_count++;
			token = token->next;
		}
		else if (token->type == WORD)
		{
			tab->args_count++;
		}
		// if (token)
		token = token->next;
	}
}
