/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:26:28 by manbengh          #+#    #+#             */
/*   Updated: 2024/12/09 20:19:29 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (tmp)
	{
		while (tmp)
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

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd: error retrieving current directory:");
		perror(" getcwd: cannot access parent directories\n");
		data->exit_status = 1;
		free(pwd);
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	ft_is_builtin(t_parse *tab, int i)
{
	if (!tab[i].args || !tab[i].args[0])
		return (1);
	if (ft_strcmp(tab[i].args[0], "env") == 0)
		return (0);
	if (ft_strcmp(tab[i].args[0], "pwd") == 0)
		return (0);
	if (ft_strcmp(tab[i].args[0], "unset") == 0)
		return (0);
	if (ft_strcmp(tab[i].args[0], "export") == 0)
		return (0);
	if (ft_strcmp(tab[i].args[0], "exit") == 0)
		return (0);
	if (ft_strcmp(tab[i].args[0], "echo") == 0)
		return (0);
	if (ft_strcmp(tab[i].args[0], "cd") == 0)
		return (0);
	return (1);
}

int	ft_built_in_comp(t_mini *data, t_parse *tab, int i)
{
	if (!tab[i].args || !tab[i].args[0])
		return (1);
	if (ft_strcmp(tab[i].args[0], "env") == 0)
		return (ft_env(data->env));
	if (ft_strcmp(tab[i].args[0], "pwd") == 0)
		return (ft_pwd(data));
	if (ft_strcmp(tab[i].args[0], "unset") == 0)
		return (ft_unset(data, &tab[i]));
	if (ft_strcmp(tab[i].args[0], "export") == 0)
		return (ft_export(data, &tab[i]));
	if (ft_strcmp(tab[i].args[0], "exit") == 0)
		return (ft_exit(data, &tab[i]));
	if (ft_strcmp(tab[i].args[0], "echo") == 0)
		return (ft_echo(&tab[i]));
	if (ft_strcmp(tab[i].args[0], "cd") == 0)
		return (ft_cd(&tab[i], data));
	return (1);
}

// env    = fini
// pwd    = fini
// echo   = fini
// cd     = normalement fini
// unset  = fini
// export = fini
// exit   = presque