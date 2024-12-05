/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:30:31 by manbengh          #+#    #+#             */
/*   Updated: 2024/12/05 16:12:44 by manbengh         ###   ########.fr       */
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
	my_home = getenv("HOME");
	if (!my_home)
		return (printf("Error : can't get HOME.\n"), 1);
	if (tab->args[1])
	{
		if (tab->args[2])
			return (printf("Erreur cd : too many arguments !\n"), 1);
		if (chdir(tab->args[1]) != 0)
			return (printf("Error : chdir fail \n"), 1);
		change_value_in_env_cd(&data->env, "OLDPWD", old_pwd,
			data->env->content);
		new_pwd = getcwd(NULL, 0);
		if (!new_pwd)
			return (printf("Error: getcwd failed\n"), 1);
		change_value_in_env_cd(&data->env, "PWD", new_pwd, data->env->content);
	}
	else
		if (chdir(my_home) != 0)
			return (printf("Error : chdir fail \n"), 1);
	free(new_pwd);
	free(old_pwd);
	return (0);
}
