/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:30:31 by manbengh          #+#    #+#             */
/*   Updated: 2025/01/23 21:28:12 by ahbey            ###   ########.fr       */
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
	if (!env[0])
		return ;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
		{
			free(tmp->value);
			free(tmp->content);
			tmp->value = ft_strdup(new_value);
			tmp->content = ft_strdup(content);
			return ;
		}
		tmp = tmp->next;
	}
}

int	else_cd(t_mini *data, char *new_pwd, char *old_pwd)
{
	char	*my_home;

	my_home = NULL;
	my_home = getenv("HOME");
	if (!my_home)
		return (printf("Error : can't get HOME.\n"), 1);
	if (chdir(my_home) != 0)
		return (printf("Error : chdir fail \n"), 1);
	change_value_in_env_cd(&data->env, "OLDPWD", old_pwd, data->env->content);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		(free(new_pwd), free(old_pwd));
		return (printf("Error: getcwd failed\n"), 1);
	}
	change_value_in_env_cd(&data->env, "PWD", new_pwd, data->env->content);
	return (0);
}

int	cd_if_env(t_mini *data, char *old_pwd, char *new_pwd)
{
	change_value_in_env_cd(&data->env, "OLDPWD", old_pwd, data->env->content);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		(free(new_pwd), free(old_pwd));
		return (printf("Error: getcwd failed\n"), 1);
	}
	change_value_in_env_cd(&data->env, "PWD", new_pwd, data->env->content);
	free(new_pwd);
	return (0);
}

int	cd_if_two(char *old_pwd, char *new_pwd)
{
	(free(new_pwd), free(old_pwd));
	return (printf("Error cd : too many arguments !\n"), 1);
}

int	ft_cd(t_parse *tab, t_mini *data)
{
	char	*new_pwd;
	char	*old_pwd;

	new_pwd = NULL;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (printf("Error : getcwd failed \n"), 1);
	if (tab->args[1])
	{
		if (tab->args[2])
			if (cd_if_two(old_pwd, new_pwd) == 1)
				return (1);
		if (chdir(tab->args[1]) != 0)
		{
			(free(new_pwd), free(old_pwd));
			return (printf("Error : chdir fail\n"), 1);
		}
		if (data->env)
			if (cd_if_env(data, old_pwd, new_pwd) == 1)
				return (1);
	}
	else if (else_cd(data, new_pwd, old_pwd) == 1)
		return (1);
	return (free(old_pwd), 0);
}
