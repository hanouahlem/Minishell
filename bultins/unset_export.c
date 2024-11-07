/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:33:03 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/07 17:12:24 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_export(t_mini *data)
// {
// 	int i;

// 	i = 0;
// 	(void)data;
// 	printf("hello export\n");
	
// 	return (0);
// }

int	add_export_env(t_mini *data, t_parse tab)
{
	int		i;
	t_env	*node;
	// t_env	*path;

	i = 1;
	node = NULL;
	// path = NULL;
	// while (tab->args[i])
	// {
		node = ft_lstnew_env(tab.args[i]);
		if (!node)
			return (1);
		ft_lstadd_back_env(&data->env, node);
		// i++;
	// }
	return (0);
}

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

int	is_key_in_env(t_mini *data, char *str, t_parse *tab, int i)
{
	t_env *tmp;

	tmp = data->env;
	while (data->env)
	{
		if (ft_strcmp(data->env->key, str) == 0)
		{
			printf("la key existe deja\n");
			free(data->env->value);
			data->env->value = find_value_for_env(tab->args[i]);
			printf("value =====> %s\n", data->env->value);
			data->env = tmp;
			return (1);
		}
		data->env = data->env->next;
	}
	data->env = tmp;
	return (0);
}
int	ft_export(t_mini *data, t_parse *tab)
{
	int i;
	char *key;
	t_env	*node;
	
	i = 1;
	node = NULL;
	while (tab->args[i])
	{
		key = find_key_for_env(tab->args[i]);
		if(check_key_export(key) == 1)
			return(1);
		if (is_key_in_env(data, key, tab, i) == 1)
		{
			printf("tete env ---------> %s\n", data->env->content);
			// printf("la key existe deja\n");
			// free(data->env->value);
			// data->env->value = find_value_for_env(tab->args[1]);
			// printf("value =====> %s\n", data->env->value);
		}
		else
		{
			node = ft_lstnew_env(tab->args[i]);
			if (!node)
				return (1);
			ft_lstadd_back_env(&data->env, node);
		}
		i++;
	}
	return (0);
}

// data->env->value = ft_substr(tab->args[i], ft_strlen_stop(tab->args[i], '=') + 1,
// 			ft_strlen(tab->args[i]));


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
