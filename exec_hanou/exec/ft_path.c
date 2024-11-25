


#include "minishell.h"

// char	**get_path(char **env)
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

int	concatene_command(t_parse *tab, char **s_path, char *my_cmd)
{
	int		i;
	char	*tmp;
	char	*full_command;

	i = 0;
	tmp = NULL;
	full_command = NULL;
	while (s_path && s_path[i] && tab->args)
	{
		tmp = ft_strjoin(s_path[i], "/");
		full_command = ft_strjoin(tmp, my_cmd);
		free(tmp);
		if (access(full_command, F_OK | X_OK) == 0)
		{
			tab->cmd = full_command;
			if (s_path)
				free_tab(s_path);
			return (1);
		}
		free(full_command);
		i++;
	}
	return (0);
}

void	find_path(t_mini *data, t_parse *tab, char *my_cmd)
{
	char	**s_path;

	if (access(my_cmd, F_OK | X_OK) == 0)
	{
		tab->cmd = my_cmd;
		return ;
	}
	s_path = get_path(data->exec->env_exec);
	if (concatene_command(tab, s_path, my_cmd) == 1)
    {
		return ;
    }
	free_tab(s_path);
	// free_everything(pip, "Error ! Can't find path ");
}
