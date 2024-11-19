/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:48:03 by manbengh          #+#    #+#             */
/*   Updated: 2024/11/14 18:27:01 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *tokenis)
{
	t_token *tmp;

	tmp = tokenis;
	printf("IN PRINT TOKEN !!!!");
	while (tmp)
	{
		printf("value == %s\n", tmp->value_t);
		printf("type == %d\n", tmp->type);
		// printf("content env : ")
		if (tmp->prev != NULL)
			printf("prev == %s\n\n", tmp->prev->value_t);
		tmp = tmp->next;
	}
}

void	print_env(t_env *env)
{
	while (env)
	{
		// printf("KEY :  %s\n", env->key);
		// printf("VALUE :  %s\n\n", env->value);
		printf("%s\n", env->content);
		env = env->next;
	}
}
