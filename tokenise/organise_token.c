/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organise_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:18:52 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/23 19:53:49 by ahbey            ###   ########.fr       */
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
	(void)size;
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

t_parse	*table_struct(t_mini *data)
{
	int		i;
	int		size;
	t_parse	*tab;

	i = 0;
	size = pipe_nbr(*data);
	print_token(data->token);
	printf("\n");
	tab = ft_calloc(sizeof(t_parse), (size + 1));
	if (!tab)
		return (NULL);
	printf("%p\n", tab);
	while (data->token)
	{
		if (data->token->type != PIPE)
			ft_parse(&tab[i], data->token);
		if (if_is_redir(data->token->type) == 0)
			data->token = data->token->next;
		if (data->token->type == PIPE)
			i++;
		if (data->token)
			data->token = data->token->next;
	}
	print_parse(tab, size);
	return (tab);
}

// ls -l | cat -re | echo asd  asd

// tab[0]
// cmd = ls
// arg = ls -l

// tab[1]
// cmd = cat
// arg = cat -re

// tab[2]
// cmd = echo
// arg = echo asd asd