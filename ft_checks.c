/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:04:13 by manbengh          #+#    #+#             */
/*   Updated: 2024/12/31 17:08:07 by ahbey            ###   ########.fr       */
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

void	init_data(t_mini *data, char **env)
{
	data->standard[0] = -1;
	data->standard[1] = -1;
	data->env = get_env(env);
	data->exec = NULL;
	data->exit_status = 0;
	g_sign_return = 0;
}

char	*process_and_expand_line(char *line, t_mini *data)
{
	line = token_negation(line);
	if (is_space_or_tab(line) == 1 || ft_quote(line) == 1
		|| ft_check_redir_in_out(line) == 1)
	{
		free(line);
		return (NULL);
	}
	line = token_positive(line);
	line = ft_expand(line, data);
	split_line(-1, line, &data->token);
	line = token_positive(line);
	return (line);
}

int	handle_signal(t_mini *data)
{
	if (g_sign_return != 0)
	{
		data->exit_status = g_sign_return ;
		g_sign_return = 0;
		return (1);
	}
	return (0);
}
