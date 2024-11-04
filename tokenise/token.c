/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:32:30 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/30 20:52:56 by ahbey            ###   ########.fr       */
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
	// if(!str)
	// 	return(NULL);
	while (line[++i])
	{
		if (line[i] == ' ')
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
			str[index_l++] = line[i];
	}
	if (index_l > 0)
		handle_token(str, &index_l, tokenis);
	free(str);
	*tokenis = add_prev(*tokenis);
}

//687 allocs, 224 frees, 238,024 bytes allocated