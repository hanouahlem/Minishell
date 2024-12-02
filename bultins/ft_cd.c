/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:30:31 by manbengh          #+#    #+#             */
/*   Updated: 2024/12/02 19:35:16 by manbengh         ###   ########.fr       */
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

void    update_env(t_mini *data, char *key, char *value)
{
        change_value_in_env_cd(&data->env, key, value, data->env->content);
}


int	ft_cd(t_parse *tab, t_mini *data)
{
	char	*my_home;
	char	*new_pwd;
	char	*old_pwd;

	old_pwd = getenv("PWD");
	if (!old_pwd)
		old_pwd = getcwd(NULL, 0);
	my_home = getenv("HOME");
	if (!my_home)
		return (printf("Error : can't get HOME.\n"), 1);
	if (tab->args[1])
	{
		if (tab->args[2])
			return (printf("Erreur cd : too many arguments !\n"), 1);
		if (ft_strcmp(tab->args[1], "~") == 0)
		{
			if (chdir(my_home) != 0)
				return (printf("Error : chdir fail \n"), 1);
		}
		if (chdir(tab->args[1]) != 0)
			return (printf("Error : chdir fail \n"), 1);
	}
	else
	{
		if (chdir(my_home) != 0)
			return (printf("Error : chdir fail \n"), 1);
	}
	update_env(data,"OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (printf("Error: getcwd failed\n"), 1);
	update_env(data, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

