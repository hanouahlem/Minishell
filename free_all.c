/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:23:16 by manbengh          #+#    #+#             */
/*   Updated: 2024/10/08 19:23:29 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (tmp)
	{
		tmp = env->next;
		free(env);
		env = tmp;
	}
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (tmp)
	{
		tmp = token->next;
		free(token);
		token = tmp;
	}
}

void	free_everything(t_mini *data)
{
	free_env(data->env);
	free_token(data->token);
}
