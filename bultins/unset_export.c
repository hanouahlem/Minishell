/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:33:03 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/09 14:30:15 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key_export(char *key)
{
	int	i;

	i = 0;
	if (!key[i] || (ft_isdigit(key[i]) == 1))
		return (printf("Error: export: `%s' : not a valid identifier\n", key),
			1);
	while (key[i])
	{
		if (ft_isalnum(key[i]) || key[i] == '_')
			i++;
		else
			return (printf("Error: export: `%s' : not a valid identifier\n",
					key), 1);
	}
	return (0);
}

int	is_key_in_env(t_mini *data, char *str)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	change_value_in_env(t_env **env, char *str, char *new_value,
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

int	ft_export(t_mini *data, t_parse *tab)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*node;

	i = 1;
	node = NULL;
	while (tab->args[i])
	{
		key = find_key_for_env(tab->args[i]);
		if (check_key_export(key) == 1)
			return (free(key), 1);
		value = find_value_for_env(tab->args[i]);
		if (is_key_in_env(data, key) == 1)
			change_value_in_env(&data->env, key, value, tab->args[i]);
		else
		{
			node = ft_lstnew_env(tab->args[i]);
			if (!node)
			{
				free(key);
				free(value);
				return (1);
			}
			ft_lstadd_back_env(&data->env, node);
		}
		i++;
		free(value);
		free(key);
	}
	return (0);
}

void	free_unset(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env->content);
}

int	ft_unset(t_mini *data, t_parse *tab)
{
	t_env	*tmp;
	t_env	*prev;
	int	i;

	tmp = data->env;
	prev = NULL;
	i = 0;
	while (tab->args[++i])
	{
		while (data->env)
		{
			if (ft_strcmp(data->env->key, tab->args[i]) == 0)
			{
				free_unset(data->env);
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

