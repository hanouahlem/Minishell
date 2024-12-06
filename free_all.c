/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:23:16 by manbengh          #+#    #+#             */
/*   Updated: 2024/12/06 20:21:38 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_mini *data)
{
	t_env	*temp;

	while (data->env)
	{
		temp = data->env->next;
		free(data->env->value);
		free(data->env->content);
		free(data->env->key);
		free(data->env);
		data->env = temp;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_token(t_mini *data)
{
	t_token	*temp;

	while (data->token)
	{
		temp = data->token->next;
		free(data->token->value_t);
		free(data->token);
		data->token = temp;
	}
}

void	free_parser(t_mini *data, t_parse *tab)
{
	int	i;

	i = 0;
	(void)data;
	while (i < tab->size_cmd)
	{
		if (tab[i].cmd)
			free(tab[i].cmd);
		if (tab[i].args)
			free_tab(tab[i].args);
		if (tab[i].filename)
			free_tab(tab[i].filename);
		if (tab[i].typefile)
			free(tab[i].typefile);
		i++;
	}
	free(tab);
}

// void	free_expand(t_expand *expand)
// {
// 	if (expand->str)
// 		free(expand->str);
// 	if (expand->new_str)
// 		free(expand->new_str);
// }

void	free_inside(t_mini *data, char *line, t_parse *tab)
{
	if (line)
		free(line);
	if (data->token)
		free_token(data);
	if (tab)
		free_parser(data, tab);
	if (data->expand)
	{
		if (data->expand->str)
			free(data->expand->str);
		if (data->expand->new_str)
			free(data->expand->new_str);
	}
}
