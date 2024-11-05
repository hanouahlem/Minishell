/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:26:28 by manbengh          #+#    #+#             */
/*   Updated: 2024/11/04 18:39:25 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_mini *data)
{
	int		i;
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

int	ft_pwd(t_mini *data)
{
	char	*pwd;

	(void)data;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd failed\n");
		// --> afficher la valeur de retour pour exit  <--
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	ft_cd(t_mini *data, t_parse *tab)
{
	char	*my_home;

	(void)data;
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
	return (0);
}

int	ft_built_in_comp(t_mini *data, t_parse *tab)
{
	printf("tab->arg[0] =====>>>> [%s]\n", tab->args[0]);
	if (!tab->args[0])
		return (1);
	if (ft_strcmp(tab->args[0], "env") == 0)
		return (ft_env(data), 0);
	if (ft_strcmp(tab->args[0], "pwd") == 0)
		return (ft_pwd(data), 0);
	if (ft_strcmp(tab->args[0], "unset") == 0)
		return (ft_unset(data), 0);
	if (ft_strcmp(tab->args[0], "export") == 0)
		return (ft_export(data), 0);
	if (ft_strcmp(tab->args[0], "exit") == 0)
		return (ft_exit(data), 0);
	if (ft_strcmp(tab->args[0], "echo") == 0)
		return (ft_echo(tab), 0);
	if (ft_strcmp(tab->args[0], "cd") == 0)
		return (ft_cd(data, tab), 0);
	return (1);
}

// env = fait
// pwd = fait
// echo = a finir
// cd = a faire
// unset = a faire
// export = a faire
// exit = a faire