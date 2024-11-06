/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:33:03 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/06 15:46:18 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_mini *data)
{
	int	i;

	i = 0;
	(void)data;
	printf("hello export\n");
	return (0);
}

void	unset_free(t_mini *data)
{
	free(data->env->key);
	free(data->env->value);
	free(data->env->content);
}

int	ft_unset(t_mini *data, t_parse *tab)
{
	t_env	*tmp;
	t_env	*prev;

	if (tab->args[1])
	{
		tmp = data->env;
		prev = NULL;
		while (data->env)
		{
			if (ft_strcmp(data->env->key, tab->args[1]) == 0)
			{
				unset_free(data);
				if (prev)
					prev->next = data->env->next;
				else
					tmp = data->env->next;
				free(data->env);
				break ;
			}
			prev = data->env;
			data->env = data->env->next;
		}
		data->env = tmp;
	}
	return (0);
}
