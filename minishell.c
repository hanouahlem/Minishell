/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:26:49 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/23 15:25:15 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int sign_return;

int is_space_or_tab(char *str)
{
	int i;

	i = 0;
	while ((str[i] && str[i] == ' ') || str[i] == '\t')
		i++;
	if (i == (int)ft_strlen(str))
		return (1);
	return (0);
}

int main(int ac, char **av, char **env)
{
	static t_mini data = {0,
						  .standard[0] = -1,
						  .standard[1] = -1};
	char *line;
	t_parse *tab;

	(void)ac;
	(void)av;
	tab = NULL;
	// signal(SIGINT, sig_management);
	// signal(SIGQUIT, sig_management);
	sign_return = 0;
	data.env = get_env(env);
	data.exec = NULL;
	line = NULL;
	data.exit_status = 0;
	data.check = 0;
	while (1)
	{
		manage_sig();
		if (data.check == 0)
			signal(SIGINT, sig_management);
		if (data.check == 1)
			signal(SIGINT, sig_management2);
		data.check = 0;
		sign_return = 0;
		if (sign_return == SIGINT)
			data.exit_status = 130;
		line = readline("Minishell 😜👀$> ");
		if (!line)
			break;
		if (!*line)
			continue;
		if (is_space_or_tab(line) == 1)
		{
			free(line);
			continue;
		}
		add_history(line);
		line = token_negation(line);
		if (ft_quote(line))
		{
			free(line);
			continue;
		}
		if (ft_check_redir_in_out(line) == 1)
		{
			free(line);
			continue;
		}
		line = token_positive(line);
		line = ft_expand(line, &data);
		split_line(-1, line, &data.token);
		line = token_positive(line);
		tab = table_struct(&data);
		data.parser = tab;
		free(line);
		if (tab->args == NULL)
		{
			free_inside(&data, NULL, tab);
			continue;
		}
		if (ft_exec(&data, data.parser) == 1)
		{
			clean_hdoc(&data);
			free_inside(&data, NULL, tab);
			continue;
		}
		clean_hdoc(&data);
		free_inside(&data, NULL, tab);
	}
	free(line);
	free_env(&data);
	rl_clear_history();
	return (0);
}
