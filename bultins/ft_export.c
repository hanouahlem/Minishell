/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:33:03 by ahbey             #+#    #+#             */
/*   Updated: 2025/01/23 21:28:53 by ahbey            ###   ########.fr       */
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

void	process_export(t_mini *data, t_parse *tab, char *key, int i)
{
	t_env	*node;
	char	*value;

	node = NULL;
	value = find_value_for_env(tab->args[i]);
	if (is_key_in_env(data, key))
		change_value_in_env(&data->env, key, value, tab->args[i]);
	else
	{
		node = ft_lstnew_env(tab->args[i]);
		if (!node)
			return (free(key), free(value));
		ft_lstadd_back_env(&data->env, node);
	}
	free(value);
}

int	ft_export(t_mini *data, t_parse *tab)
{
	int		i;
	char	*key;

	i = 1;
	while (tab->args[i])
	{
		key = find_key_for_env(tab->args[i]);
		if (check_key_export(key) == 1)
			return (free(key), 1);
		process_export(data, tab, key, i);
		i++;
		free(key);
	}
	return (0);
}
