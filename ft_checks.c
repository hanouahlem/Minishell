/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:04:13 by manbengh          #+#    #+#             */
/*   Updated: 2024/12/30 17:24:18 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space_or_tab(char *str)
{
	int	i;

	i = 0;
	while ((str[i] && str[i] == ' ') || str[i] == '\t')
		i++;
	if (i == (int)ft_strlen(str))
		return (1);
	return (0);
}

int	check_main(t_mini *data, char *line, t_parse *tab)
{
	(void)data;
	(void)tab;
	line = token_negation(line);
	if (is_space_or_tab(line) == 1 || ft_quote(line) == 1
		|| ft_check_redir_in_out(line) == 1)
		return (1);
	// line = token_positive(line);
	// line = ft_expand(line, data);
	// split_line(-1, line, &data->token);
	// line = token_positive(line);
	// tab = table_struct(data);
	// data->parser = tab;
	// free(line);
	// if (tab->args == NULL)
	// {
	// 	free_inside(data, NULL, tab);
	// 	return (1);
	// }
	return (0);
}
