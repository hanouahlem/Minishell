/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:26:49 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/31 17:09:20 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sign_return ;

static char	*read_and_process_line(t_mini *data, char *line)
{
	add_history(line);
	return (process_and_expand_line(line, data));
}

static int	handle_execution(t_mini *data, t_parse *tab)
{
	if (tab->args == NULL)
	{
		free_inside(data, NULL, tab);
		return (1);
	}
	if (ft_exec(data, data->parser) == 1)
	{
		clean_hdoc(data);
		free_inside(data, NULL, tab);
		return (1);
	}
	clean_hdoc(data);
	free_inside(data, NULL, tab);
	return (0);
}

static void	minishell_loop(t_mini *data)
{
	char	*line;
	t_parse	*tab;

	tab = NULL;
	line = NULL;
	while (1)
	{
		manage_sig();
		if (handle_signal(data) == 1)
			continue ;
		line = readline("Minishell 😜👀$> ");
		if (!line)
			break ;
		if (!*line)
			continue ;
		line = read_and_process_line(data, line);
		tab = table_struct(data);
		data->parser = tab;
		free(line);
		if (handle_execution(data, tab) == 1)
			continue ;
	}
}

int	main(int ac, char **av, char **env)
{
	static t_mini	data = {0, .standard[0] = -1, .standard[1] = -1};

	(void)ac;
	(void)av;
	init_data(&data, env);
	minishell_loop(&data);
	free_env(&data);
	rl_clear_history();
	return (0);
}
