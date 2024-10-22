/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:26:28 by manbengh          #+#    #+#             */
/*   Updated: 2024/10/21 18:52:10 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_mini *data)
{
	int	i;

	i = 0;
	if (data->env)
	{
		while (data->env->next)
		{
			printf("%s\n", data->env->content);
			data->env = data->env->next;
		}
		return (0);
	}
	return (1);
}
int ft_pwd(t_mini *data)
{
	(void)data;
	printf("hello pwd\n");
	return(0);
}

int ft_cd(t_mini *data)
{
	(void)data;
	printf("hello cd\n");
	return(0);
}

int ft_echo (t_mini *data)
{
	(void)data;
	printf("hello echo\n");
	return(0);
}

int	ft_built_in_comp(t_mini *data)
{
	(void)data;
	// printf("cmd=============>> %s",data->parse->cmd);
	// if (ft_strcmp(data->parse->cmd, "env") == 0)
	// 	return(printf("hello"),ft_env(data),0);
	// else if (ft_strcmp(data->token->value_t, "pwd")== 0)
	// 	ft_pwd(data);
	// else if (ft_strcmp(data->token->value_t, "cd"))
	// 	ft_cd(data);
	// else if (ft_strcmp(data->token->value_t, "echo"))
	// 	ft_echo(data);
	// else if (ft_strcmp(data->token->value_t, "unset"))
	// 	ft_unset(data);
	// else if (ft_strcmp(data->token->value_t, "export"))
	// 	ft_export(data);
	// else if (ft_strcmp(data->token->value_t, "exit"))
	// 	ft_exit(data);
	return (1);
}
