/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:48:03 by manbengh          #+#    #+#             */
/*   Updated: 2024/10/14 20:07:28 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *tokenis)
{
	while (tokenis)
	{
		printf("value == %s\n", tokenis->value_t);
		printf("type == %d\n", tokenis->type);
                // printf("content env : ")
		if (tokenis->prev != NULL)
			printf("prev == %s\n\n", tokenis->prev->value_t);
		tokenis = tokenis->next;
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
