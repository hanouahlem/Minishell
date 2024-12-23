
#include "minishell.h"


void	env_in_tab(t_mini *data)
{
	t_env *tmp;
	int i;
	int env_size;

	tmp = data->env;
	env_size = 0;
	i = 0;
	if (!data->exec)
	{
		data->exec = malloc(sizeof(t_exec));
		if (!data->exec)
		{
			perror("malloc failed for data->exec");
			return ;
		}
	}
	data->exec->env_exec = NULL;
	while (tmp)
	{
		env_size++;
		tmp = tmp->next;
	}
	if (data->exec->env_exec)
		free(data->exec->env_exec);
	data->exec->env_exec = malloc(sizeof(char *) * (env_size + 1));
	if (!data->exec->env_exec)
	{
		perror("malloc failed for data->exec->env_exec");
		return ;
	}
	tmp = data->env;
	while (tmp)
	{
		data->exec->env_exec[i] = tmp->content;
		// printf("env_exec[i] -> %s\n", data->exec->env_exec[i]);
		i++;
		tmp = tmp->next;
	}
	data->exec->env_exec[i] = NULL;
}

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
	char *path_tmp;
	char *res;

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
	char **path;
	char *res;

	if (cmd == NULL)
	{
		ft_printf("Error: %s: command not found\n", cmd);
		return (NULL);
	}
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (!env)
		return (NULL);
	path = env;
	if (ft_strrchr(cmd, '/') == 0)
	{
		res = give_up(path, cmd);
		if (res)
			return (res);
	}
	ft_printf("Error: command not found: %s\n", cmd);
	return (NULL);
}

void	env_in_tab_exec(t_mini *data)
{
	t_env *tmp;
	int i;
	int env_size;

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
	{
		perror("malloc failed for data->exec->env_exec");
		return ;
	}
	tmp = data->env;
	while (tmp)
	{
		data->exec->env_exec[i] = tmp->content;
		// printf("env_exec[i] -> %s\n", data->exec->env_exec[i]);
		i++;
		tmp = tmp->next;
	}
	data->exec->env_exec[i] = NULL;
}
