/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:23:16 by manbengh          #+#    #+#             */
/*   Updated: 2024/10/30 15:37:20 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_mini *data)
{
	t_env	*temp;

	printf("Free Env !\n");
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
	while (tab[i])
	{
		printf("inside free_tab =====> %s\n", tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
	free(tab);
}

void	free_token(t_token *token)
{
	t_token	*temp;

	printf("Free Token !\n");
	while (token)
	{
		printf("free_token ====> %s\n", token->value_t);
		temp = token->next;
		free(token->value_t);
		free(token);
		token = temp;
	}
}

void	free_parser(t_mini *data, t_parse *tab)
{
	int	i;

	i = 0;
	(void)data;
	printf("Free parser !!!\n");
	while (i < tab->size_cmd)
	{
		if (tab[i].cmd)
		{
			printf("cmd --> %s\n", tab[i].cmd);
			free(tab[i].cmd);
		}
		if (tab[i].cmd)
		{
			printf("cmd --> %s\n", tab[i].cmd);
			free(tab[i].cmd);
		}
		if (tab[i].args)
		{
			free_tab(tab[i].args);
		}
		if (tab[i].filename)
		{
			free_tab(tab[i].filename);
		}
		if (tab[i].typefile)
		{
			// printf("typefile -> %i\n", tab[i].typefile);
			free(tab[i].typefile);
		}
		if (tab[i].typefile)
		{
			// printf("typefile -> %i\n", tab[i].typefile);
			free(tab[i].typefile);
		}
		printf("i ------> %i\n", i);
		i++;
	}
	free(tab);
}


void	free_expand(t_expand *exp)
{
	if (exp)
	{
		if (exp->new_str)
			free(exp->new_str);
		if (exp->new_str)
			free(exp->new_str);
		free(exp);
	}
}

void	free_inside(t_mini *data, char *line, t_parse *tab)
{
	// printf("---> PARSER IN MAINS \n");
	// print_parse(tab, pipe_nbr(*data));
	(void)tab;
	(void)tab;
	if (line)
		free(line);
	if (data->token)
		free_token(data->token);
	// if (tab)
	// 	free_parser(data, tab);
	// if (data->expand)
	// 	free_expand(data->expand);
}
