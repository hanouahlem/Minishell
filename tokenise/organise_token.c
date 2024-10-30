/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organise_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:18:52 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/30 15:07:52 by manbengh         ###   ########.fr       */
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

void	ft_parse(t_parse *tab, t_token *tokenis)
{
	if (if_is_redir(tokenis->type) == 0)
	{
		// stocker les redir ET fichiers
		tab->typefile[tab->typelen] = tokenis->type;
		tab->filename[tab->typelen] = strdup(tokenis->next->value_t);
		tab->typelen++;
	}
	else
	{
		// stocker les arg
		tab->args[tab->argslen++] = strdup(tokenis->value_t);
	}
}

void	print_parse(t_parse *tab, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		printf("MY COMMAND {%s}\n", tab[i].args[0]);
		j = 0;
		printf("MY ARG ");
		while (tab[i].args[j])
		{
			printf("{%s}", tab[i].args[j]);
			j++;
		}
		j = 0;
		printf("\n");
		printf("MY FILES | REDIR\n");
		while (tab[i].filename[j])
		{
			printf("{%i}", tab[i].typefile[j]);
			printf("{%s}\n", tab[i].filename[j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	ft_count_elements(t_mini *data, t_parse *tab)
{
	t_token	*token = data->token;

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
			token = token->next;  // Avancer si redirection
		}
		else if (token->type == WORD)
		{
			tab->args_count++;
		}
		token = token->next;
	}
}

void	ft_allocate_parse(t_parse *tab)
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

t_parse	*table_struct(t_mini *data)
{
	int		i;
	int		size;
	t_parse	*tab;
	t_token	*original_token;

	i = 0;
	original_token = data->token;
	tab = NULL;
	size = pipe_nbr(*data);
	tab = ft_calloc(sizeof(t_parse), (size + 1));
	if (!tab)
		return (NULL);
	tab->size_cmd = size;
	while (data->token)
	{
		ft_count_elements(data, &tab[i]);
		ft_allocate_parse(&tab[i]);
		while (data->token && data->token->type != PIPE)
		{
			ft_parse(&tab[i], data->token);
			if (if_is_redir(data->token->type) == 0)
				data->token = data->token->next;
			data->token = data->token->next;
		}
		if (data->token && data->token->type == PIPE)
			data->token = data->token->next;
		i++;
	}
	data->token = original_token;
	print_parse(tab, size);
	return (tab);
}
