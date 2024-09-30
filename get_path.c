
#include "minishell.h"

void	get_env(char **env)
{
	int		i;
	env_t	*node;
	env_t	*path;

	i = 0;
	node = NULL;
	path = NULL;
	while (env[i])
	{
		node = ft_lstnew_env(env[i]);
		if (!node)
			return ;
		ft_lstadd_back_env(&path, node);
		i++;
	}
	// while (path)
	// {
	// 	printf("%s\n", path->content);
	// 	printf("%s\n", path->value);
	// 	path = path->next;
	// }
}

char	*find_key_for_env(char *my_env)
{
	char	*key;

	key = ft_substr(my_env, 0, ft_strlen_stop(my_env, '='));
	return (key);
}

char	*find_value_for_env(char *my_env)
{
	char	*value;

	value = ft_substr(my_env, ft_strlen_stop(my_env, '='), ft_strlen(my_env));
	return (value);
}

int	ft_strlen_stop(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}
