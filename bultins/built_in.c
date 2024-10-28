/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:26:28 by manbengh          #+#    #+#             */
/*   Updated: 2024/10/28 15:07:18 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_mini *data)
{
	int	i;
	t_env	*tmp;

	i = 0;
	tmp = data->env;
	if (tmp)
	{
		while (tmp->next)
		{
			printf("%s\n", tmp->content);
			tmp = tmp->next;
		}
		return (0);
	}
	return (1);
}
int ft_pwd(t_mini *data)
{
	(void)data;
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd failed\n");
		// --> afficher la valeur de retour pour exit  <--
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return(0);
}

int ft_cd(t_mini *data)
{
	(void)data;
	printf("hello cd\n");
	return(0);
}

int	ft_built_in_comp(t_mini *data, t_parse *tab)
{
	if (ft_strcmp(tab->args[0], "env") == 0)
		return(ft_env(data),0);
	if (ft_strcmp(tab->args[0], "pwd") == 0)
		return (ft_pwd(data), 0);
	if (ft_strcmp(tab->args[0], "unset") == 0)
		return (ft_unset(data), 0);
	if (ft_strcmp(tab->args[0], "export") == 0)
		return (ft_export(data), 0);
	if (ft_strcmp(tab->args[0], "exit") == 0)
		return (ft_exit(data), 0);
	if (ft_strcmp(tab->args[0], "echo") == 0)
		return (ft_echo(data, tab) ,0);
	if (ft_strcmp(tab->args[0], "cd") == 0)
		return (ft_cd(data), 0);
	return (1);
}
