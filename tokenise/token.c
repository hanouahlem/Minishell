/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:32:30 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/15 16:53:47 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_redir(char *str, int i)
// {
// 	if (str[i] == '<')
// 	{
// 		if (str[i + 1] != '<')
// 			return (1);
// 		else if (str[i + 1] == '<')
// 			return (2);
// 	}
// 	if (str[i] == '>')
// 	{
// 		if (str[i + 1] != '>')
// 			return (3);
// 		else if (str[i + 1] == '>')
// 			return (4);
// 	}
// 	return (0);
// }

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
	str[1] = '\0';
	node_t = ft_lstnew_tok(str);
	ft_lstadd_back_tok(tokenis, node_t);
}

void	split_line(int i, char *line, t_token **tokenis)
{
	int	index_l = 0;
	char	*str;

	index_l = 0;
	str = ft_strdup(line);
	while (line[i])
	{
		// printf("line [i] == {%c}", line[i]);
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
		i++;
	}
	if (index_l > 0)
		handle_token(str, &index_l, tokenis);
	*tokenis = add_prev(*tokenis);
}

	// while (tokenis)
	// {
	// 	printf("value == %s\n", tokenis->value_t);
	// 	printf("type == %d\n", tokenis->type);
	// 	if (tokenis->prev != NULL)
	// 		printf("prev == %s\n\n", tokenis->prev->value_t);
	// 	tokenis-> tokenis->next;
	// }
	// while (tokenis)
	// {
	// 	printf("%s --> ", tokenis->value_t);
	// 	printf("%d\n", tokenis->type);
	// 	tokenis = tokenis->next;
	// }