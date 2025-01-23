/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:25:21 by manbengh          #+#    #+#             */
/*   Updated: 2024/12/30 16:40:14 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_unset(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env->content);
}

void	remove_env_node(t_mini *data, t_env *prev, t_env *node)
{
	if (prev)
		prev->next = node->next;
	else
		data->env = node->next;
	free_unset(node);
	free(node);
}

int	unset_key_in_env(t_mini *data, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = data->env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			remove_env_node(data, prev, tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	ft_unset(t_mini *data, t_parse *tab)
{
	int	i;

	i = 1;
	while (tab->args[i])
	{
		unset_key_in_env(data, tab->args[i]);
		i++;
	}
	return (0);
}
