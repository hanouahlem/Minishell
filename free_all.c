/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:23:16 by manbengh          #+#    #+#             */
/*   Updated: 2024/10/27 02:06:12 by ahbey            ###   ########.fr       */
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
// 	while (data->token)
// 	{
// 		free(data->token);
// 		data->token = data->token->next;
// 	}
// }

void	free_token(t_mini *data)
{
	t_token *temp;

	while (data->token)
	{
		temp = data->token->next;
		free(data->token->value_t);
		free(data->token);
		data->token = temp;
	}
}

// void	free_parse(t_parse *parse)
// {
// 	int i;
	
// 	i = 0;
// 	while(i < )
// }


void	free_inside(t_mini *data, char *line)
{
	if (line)
		free(line);
	if (data->token)
		free_token(data);
}
