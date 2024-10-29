/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:23:16 by manbengh          #+#    #+#             */
/*   Updated: 2024/10/29 15:37:03 by ahbey            ###   ########.fr       */
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

void	free_parse(t_parse *tab, t_mini *data)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < data->size)
	{
		if (tab[i].args)
		{
			j = 0;
			while (j < tab[i].argslen)
			{
				free(tab[i].args[j]);
				j++;
			}
			free(tab[i].args);
		}
		if (tab[i].filename)
		{
			j = 0;
			while (j < tab[i].typelen)
			{
				free(tab[i].filename[j]);
				j++;
			}
			free(tab[i].filename);
		}
		free(tab[i].typefile);
		i++;
	}
	free(tab);
}

void	free_inside(t_mini *data, char *line)
{
	if (line)
		free(line);
	if (data->token)
		free_token(data);
	if(data->parser)
		free_parse(data->parser, data);
}
