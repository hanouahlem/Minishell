/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:32:30 by ahbey             #+#    #+#             */
/*   Updated: 2024/09/26 19:52:18 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(char *str, int i)
{
	if (str[i] == '<')
	{
		if (str[i + 1] != '<')
			return (1);
		else if (str[i + 1] == '<')
			return (2);
	}
	if (str[i] == '>')
	{
		if (str[i + 1] != '>')
			return (3);
		else if (str[i + 1] == '>')
			return (4);
	}
	return (0);
}

void	split_line(char *line, t_token *tokenis)
{
	int	i;
	int	index_l;
	char	*str;
	t_token	*node_t;

	i = 0;
	index_l = 0;
	node_t = NULL;
	str = ft_strdup(line);
	while (line[i])
	{
		if (line[i] == ' ')
		{
			if (index_l > 0)
			{
				str[index_l] = '\0';
				node_t = ft_lstnew_tok(str);
				ft_lstadd_back_tok(&tokenis, node_t);
				index_l = 0;
			}
		}
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			if (index_l > 0)
			{
				str[index_l] = '\0';
				node_t = ft_lstnew_tok(str);
				ft_lstadd_back_tok(&tokenis, node_t);
				index_l = 0;
			}
			str[0] = line[i];
			str[1] = '\0';
			node_t = ft_lstnew_tok(str);
			ft_lstadd_back_tok(&tokenis, node_t);
		}
		else
			str[index_l++] = line[i];
		i++;
	}
	if (index_l > 0)
	{
		str[index_l] = '\0';
		node_t = ft_lstnew_tok(str);
		ft_lstadd_back_tok(&tokenis, node_t);
	}
	while (tokenis)
	{
		printf("%s --> ", tokenis->value_t);
		printf("%d\n", tokenis->type);
		tokenis = tokenis->next;
	}
}
