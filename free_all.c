/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:23:16 by manbengh          #+#    #+#             */
/*   Updated: 2024/10/30 15:03:16 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_env(t_env *env)
// {
// 	t_env	*tmp;

// 	while (tmp)
// 	{
// 		tmp = env->next;
// 		free(env);
// 		env = tmp;
// 	}
// }


// void	free_token(t_mini *data)
// {
// 	t_token	*temp;

// 	printf("Free Token !\n");
// 	while (data->token)
// 	{
// 		temp = data->token->next;
// 		free(data->token->value_t);
// 		free(data->token);
// 		data->token = temp;
// 	}
// }

// void	free_parse(t_parse *tab, t_mini *data)
// {
// 	int	i;
// 	int	j;
	
// 	i = 0;
// 	while (i < data->size)
// 	{
// 		if (tab[i].args)
// 		{
// 			j = 0;
// 			while (j < tab[i].argslen)
// 			{
// 				free(tab[i].args[j]);
// 				j++;
// 			}
// 			free(tab[i].args);
// 		}
// 		if (tab[i].filename)
// 		{
// 			j = 0;
// 			while (j < tab[i].typelen)
// 			{
// 				free(tab[i].filename[j]);
// 				j++;
// 			}
// 			free(tab[i].filename);
// 		}
// 		free(tab[i].typefile);
// 		i++;
// 	}
// 	free(tab);
// }

// void	free_inside(t_mini *data, char *line, t_parse *tab)
// {
// 	// printf("---> PARSER IN MAINS \n");
// 	// print_parse(tab, pipe_nbr(*data));
// 	// (void)tab;
// 	if (line)
// 		free(line);
// 	if (data->token)
// 		free_token(data);
// 	if(data->parser)
// 		free_parse(tab, data);
// }

// void	free_env(t_mini *data)
// {
// 	t_env	*temp;

// 	printf("Free Env !\n");
// 	while (data->env)
// 	{
// 		temp = data->env->next;
// 		free(data->env->value);
// 		free(data->env->content);
// 		free(data->env->key);
// 		free(data->env);
// 		data->env = temp;
// 	}
// }

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
}

void	free_token(t_mini *data)
{
	t_token	*temp;

	printf("Free Token !\n");
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
	printf("Free parser !!!\n");
	printf("size ----> %i\n", tab->size_cmd);
	while (i < tab->size_cmd)
	{
		if (tab[i].cmd)
		{
			printf("cmd --> %s\n", tab[i].cmd);
			free(tab[i].cmd);
		}
		if (tab[i].args)
		{
			printf("args[0] -> %s\n", tab[i].args[0]);
			free_tab(tab[i].args);
		}
		if (tab[i].filename)
		{
			printf("filename[0] -> %s\n", tab[i].filename[0]);
			free_tab(tab[i].filename);
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

void	free_inside(t_mini *data, char *line, t_parse *tab)
{
	// printf("---> PARSER IN MAINS \n");
	// print_parse(tab, pipe_nbr(*data));
	(void)tab;
	if (line)
		free(line);
	if (data->token)
		free_token(data);
	if (tab)
	{
		free_parser(data, tab);
	}
}