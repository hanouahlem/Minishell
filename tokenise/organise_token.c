/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organise_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:18:52 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/23 16:54:24 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_parse(t_parse *tab, t_token *tokenis)
{
	if (if_is_redir(tokenis->type) == 0 && tab->typelen < tab->typefile_count)
	{
		tab->typefile[tab->typelen] = tokenis->type;
		tab->filename[tab->typelen] = ft_strdup(tokenis->next->value_t);
		tab->typelen++;
	}
	else
	{
		tab->args[tab->argslen++] = ft_strdup(tokenis->value_t);
	}
}

void ft_allocate_parse(t_parse *tab)
{
	tab->args = ft_calloc(sizeof(char *), (tab->args_count + 1));
	tab->typefile = ft_calloc(sizeof(int), (tab->typefile_count + 1));
	tab->filename = ft_calloc(sizeof(char *), (tab->filename_count + 1));
	if (!tab->args || !tab->typefile || !tab->filename)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}
}

void while_token(t_mini *data, t_parse *tab, int *i)
{
	while (data->token && data->token->type != PIPE)
	{
		ft_parse(&tab[*i], data->token);
		if (if_is_redir(data->token->type) == 0)
			data->token = data->token->next;
		data->token = data->token->next;
	}
	if (data->token && data->token->type == PIPE)
		data->token = data->token->next;
}

t_parse *table_struct(t_mini *data)
{
	int i;
	int size;
	t_parse *tab;
	t_token *original_token;

	i = 0;
	tab = NULL;
	original_token = data->token;
	size = pipe_nbr(*data);
	tab = ft_calloc(sizeof(t_parse), (size + 1));
	if (!tab)
		return (NULL);
	tab->size_cmd = size;
	while (data->token)
	{
		ft_count_elements(data, &tab[i]);
		ft_allocate_parse(&tab[i]);
		while_token(data, tab, &i);
		i++;
	}
	data->token = original_token;
	return (tab);
}
