/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:30:31 by manbengh          #+#    #+#             */
/*   Updated: 2024/12/09 18:35:12 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	change_value_in_env_cd(t_env **env, char *str, char *new_value,
		char *content)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
		{
			free(tmp->value);
			free(tmp->content);
			tmp->value = ft_strdup(new_value);
			tmp->content = ft_strdup(content);
			break ;
		}
		tmp = tmp->next;
	}
}

int	ft_cd(t_parse *tab, t_mini *data)
{
	char	*my_home;
	char	*new_pwd;
	char	*old_pwd;

	new_pwd = NULL;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (printf("Error : getcwd failed \n"), 1);
	my_home = getenv("HOME");
	if (!my_home)
		return (printf("Error : can't get HOME.\n"), 1);
	if (tab->args[1])
	{
		if (tab->args[2])
		{
			(free(new_pwd), free(old_pwd));
			return (printf("Error cd : too many arguments !\n"), 1);
		}
		if (chdir(tab->args[1]) != 0)
		{
			(free(new_pwd), free(old_pwd));
			return (printf("Error : chdir fail\n"), 1);
		}
		change_value_in_env_cd(&data->env, "OLDPWD", old_pwd,
			data->env->content);
		new_pwd = getcwd(NULL, 0);
		if (!new_pwd)
		{
			(free(new_pwd), free(old_pwd));
			return (printf("Error: getcwd failed\n"), 1);
		}
		change_value_in_env_cd(&data->env, "PWD", new_pwd, data->env->content);
	}
	else
	{
		if (chdir(my_home) != 0)
			return (printf("Error : chdir fail \n"), 1);
		change_value_in_env_cd(&data->env, "OLDPWD", old_pwd,
			data->env->content);
		new_pwd = getcwd(NULL, 0);
		if (!new_pwd)
		{
			(free(new_pwd), free(old_pwd));
			return (printf("Error: getcwd failed\n"), 1);
		}
		change_value_in_env_cd(&data->env, "PWD", new_pwd, data->env->content);
	}
	(free(new_pwd), free(old_pwd));
	return (0);
}



// int	check_cd_args(t_mini *data, char **cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i])
// 		i++;
// 	if (i > 2)
// 	{
// 		ft_printf("cd : too many arguments\n");
// 		data->exit_status = 1;
// 		return (0);
// 	}
// 	return (1);
// }


// char	*get_home_env(t_env *env)
// {
// 	t_env	*tmp;

// 	tmp = env;
// 	while (tmp)
// 	{
// 		if (!ft_strcmp(tmp->key, "HOME"))
// 			return ((tmp->value));
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// int	ft_cd(t_parse *tab, t_mini *data)
// {
// 	int		ret;
// 	char	*path;

// 	if (!check_cd_args(data, tab->args))
// 		return (0);
// 	if (!tab->args[0])
// 	{
// 		path = get_home_env(data->env);
// 		if (!path)
// 		{
// 			data->exit_status = 1;
// 			return (0);
// 		}
// 	}
// 	else
// 		path = tab->args[1];
// 	ret = chdir(path);
// 	if (ret == -1)
// 	{
// 		ft_printf("cd: %s: No such file or directory\n", tab->args[1]);
// 		data->exit_status = 1;
// 		return (0);
// 	}
// 	return (1);
// }

