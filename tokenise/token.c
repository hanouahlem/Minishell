/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:32:30 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/09 19:17:57 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_token(char *str, int *index_l, t_token **tokenis)
{
	t_token	*node_t;

	str[*index_l] = '\0';
	node_t = ft_lstnew_tok(str);
	ft_lstadd_back_tok(tokenis, node_t);
	*index_l = 0;
}

void	process_special_char(char *line, char *str, int *i, t_token **tokenis)
{
	t_token	*node_t;

	str[0] = line[*i];
	if (line[(*i) + 1] == '>' || line[(*i) + 1] == '<')
	{
		*i += 1;
		str[1] = line[*i];
		str[2] = '\0';
	}
	else
		str[1] = '\0';
	node_t = ft_lstnew_tok(str);
	ft_lstadd_back_tok(tokenis, node_t);
}

void	split_line(int i, char *line, t_token **tokenis)
{
	int		index_l;
	char	*str;

	index_l = 0;
	str = ft_strdup(line);
	while (line[++i])
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			if (index_l > 0)
				handle_token(str, &index_l, tokenis);
		}
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			if (index_l > 0)
				handle_token(str, &index_l, tokenis);
			process_special_char(line, str, &i, tokenis);
		}
		else
			str[index_l++] = (line[i] ^ (line[i] >> 31)) - (line[i] >> 31);
	}
	if (index_l > 0)
		handle_token(str, &index_l, tokenis);
	*tokenis = add_prev(*tokenis);
	free(str);
}
// else
// {
// 	str[index_l++] = line[i];
// 	if (str[index_l - 1] < 0)
// 		str[index_l - 1] *= -1;
// }