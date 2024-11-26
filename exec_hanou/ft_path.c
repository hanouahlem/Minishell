
#include "minishell.h"

void	free_resources(t_mini *data)
{
	int	i;

	i = 0;
	while (i < data->parser->size_cmd - 1)
	{
		if (data->exec->pipes[i])
			free(data->exec->pipes[i]);
		i++;
	}
	free(data->exec->pid);
}

// char	**get_path_exec(char **env)
// {
// 	int		j;
// 	int		i;
// 	int		u;
// 	char	**res;

// 	u = 5;
// 	j = 0;
// 	i = -1;
// 	while (env[++i])
// 	{
// 		while (env[i][j] && env[i][j] == "PATH="[j])
// 		{
// 			j++;
// 			if (j == 5 && env[i][u])
// 			{
// 				res = ft_split(&env[i][u], ':');
// 				return (res);
// 			}
// 		}
// 	}
// 	return (NULL);
// }

// int	concatene_command(t_parse *tab, char **s_path, char *my_cmd)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*full_command;

// 	i = 0;
// 	tmp = NULL;
// 	full_command = NULL;
// 	while (s_path && s_path[i] && tab->args)
// 	{
// 		tmp = ft_strjoin(s_path[i], "/");
// 		full_command = ft_strjoin(tmp, my_cmd);
// 		free(tmp);
// 		if (access(full_command, F_OK | X_OK) == 0)
// 		{
// 			tab->cmd = full_command;
// 			if (s_path)
// 				free_tab(s_path);
// 			return (1);
// 		}
// 		free(full_command);
// 		i++;
// 	}
// 	return (0);
// }




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

// void	find_path(t_mini *data, t_parse *tab, char *my_cmd)
// {
// 	char	**s_path;

// 	if (access(my_cmd, F_OK | X_OK) == 0)
// 	{
// 		tab->cmd = my_cmd;
// 		return ;
// 	}
// 	s_path = get_path_exec(data->exec->env_exec);
// 	if (give_way_cmd(data->exec->env_exec, my_cmd) == 1)
//     {
// 		return ;
//     }
// 	free_tab(s_path);
// 	// free_everything(pip, "Error ! Can't find path ");
// }