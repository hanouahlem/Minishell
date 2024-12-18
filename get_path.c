/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:31:28 by manbengh          #+#    #+#             */
/*   Updated: 2024/12/18 19:39:31 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *get_env(char **env)
{
	int i;
	t_env *node;
	t_env *path;

	i = 0;
	node = NULL;
	path = NULL;
	if (!env[0])
		printf("No ENV\n");
	while (env[i])
	{
		node = ft_lstnew_env(env[i]);
		if (!node)
			return (NULL);
		ft_lstadd_back_env(&path, node);
		i++;
	}
	return (path);
}
// while (path)
// {
// 	printf("KEY :  %s\n", path->key);
// 	printf("VALUE :  %s\n\n", path->value);
// 	path = path->next;
// }

char *find_key_for_env(char *my_env)
{
	char *key;

	key = ft_substr(my_env, 0, ft_strlen_stop(my_env, '='));
	return (key);
}

char *find_value_for_env(char *my_env)
{
	char *value;

	value = ft_substr(my_env, ft_strlen_stop(my_env, '=') + 1,
					  ft_strlen(my_env));
	return (value);
}

int ft_strlen_stop(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}
