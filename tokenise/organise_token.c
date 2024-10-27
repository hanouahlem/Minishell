/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organise_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:18:52 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/26 22:45:10 by ahbey            ###   ########.fr       */
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
	// (void)size;
	while (i < size)
	{
		printf("MY COMMAND {%s}\n", tab[i].args[0]);
		j = 0;
		printf("MY ARG ");
		// if(!tab)
		// 	return(printf(""))
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

void	ft_count_elem(t_mini *data)
{
	t_token *tmp;
	
	data->parser->args_count = 0;
	data->parser->filename_count = 0;
	data->parser->typefile_count = 0;
	
	tmp = data->token;
	while (tmp && tmp->type != PIPE)
	{
		if (if_is_redir(tmp->type) == 0)
		{
			data->parser->typefile_count++;
			if (tmp->next && tmp->next->type == WORD)
				data->parser->filename_count++;
			tmp = tmp->next;
		}
		else if (tmp->type == WORD)
		{
			data->parser->args_count++;
		}
		tmp = tmp->next;
	}
	// printf("hellooooooo1");
}

// void	ft_malloc(t_mini data)
// {
// tab[i].args = ft_calloc(sizeof(char *), (data->args_count + 1));
// tab[i].typefile = ft_calloc(sizeof(int), (data->typefile_count + 1));
// tab[i].filename = ft_calloc(sizeof(char *), (data->filename_count + 1));
// }

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
	while (data->token)
	{
		printf("hello\n");
		// ft_count_elem(data);
		// ft_malloc();
		// printf("nbr filename ==> %d", data->parser->filename_count);
		// printf("nbr args ==> %d", data->parser->args_count);
		// printf("nbr filetype  ==> %d", data->parser->typefile_count);
		tab[i].args = ft_calloc(sizeof(char *), (tab->args_count));
		tab[i].typefile = ft_calloc(sizeof(int), (tab->typefile_count));
		tab[i].filename = ft_calloc(sizeof(char *), (tab->filename_count));
		if (!tab->args || !tab->typefile || !tab->filename)
			return (0);
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

// int	nbr_token_after(t_token *token)
// {
// 	int	count_last_pipe;
// 	int	found_pipe;

// 	count_last_pipe = 0;
// 	found_pipe = 0;
// 	while (token)
// 	{
// 		if (token->type == PIPE)
// 		{
// 			found_pipe = 1;
// 			count_last_pipe = 0;
// 		}
// 		else
// 		{
// 			count_last_pipe++;
// 		}
// 		token = token->next;
// 	}
// 	if (found_pipe)
// 		return (count_last_pipe);
// 	else
// 		return (count_last_pipe);
// }
