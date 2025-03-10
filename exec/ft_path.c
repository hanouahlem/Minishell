/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:25:12 by manbengh          #+#    #+#             */
/*   Updated: 2024/12/30 15:25:12 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_exec(char **env)
{
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (ft_split(*env + 5, ':'));
		env++;
	}
	return (NULL);
}

char	*give_up(char **path, char *cmd)
{
	char	*path_tmp;
	char	*res;

	while (*path)
	{
		path_tmp = ft_strjoin(*path, "/");
		res = ft_strjoin(path_tmp, cmd);
		free(path_tmp);
		if (access(res, X_OK) == 0)
			return (res);
		free(res);
		path++;
	}
	return (NULL);
}

char	*give_way_cmd(char **env, char *cmd)
{
	char	**path;
	char	*res;

	if (cmd == NULL)
	{
		ft_printf("Error: %s: command not found\n", cmd);
		return (NULL);
	}
	if (!env)
		return (NULL);
	path = env;
	if (ft_strrchr(cmd, '/') == 0)
	{
		res = give_up(path, cmd);
		if (res)
			return (res);
	}
	else
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	ft_printf("Error: %s: command not found\n", cmd);
	return (NULL);
}

void	env_in_tab_exec(t_mini *data)
{
	t_env	*tmp;
	int		i;
	int		env_size;

	tmp = data->env;
	env_size = 0;
	i = 0;
	data->exec->env_exec = NULL;
	while (tmp)
	{
		env_size++;
		tmp = tmp->next;
	}
	data->exec->env_exec = malloc(sizeof(char *) * (env_size + 1));
	if (!data->exec->env_exec)
		return (perror("malloc failed for data->exec->env_exec"));
	tmp = data->env;
	while (tmp)
	{
		data->exec->env_exec[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	data->exec->env_exec[i] = NULL;
}
