/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:28:00 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/14 18:29:36 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *tokenis)
{
	t_token *tmp;

	tmp = tokenis;
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

void	print_parse(t_parse *tab, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		printf("MY COMMAND {%s}\n", tab[i].args[0]);
		j = 0;
		printf("MY ARG ");
		while (tab[i].args[j])
		{
			printf("{%s}", tab[i].args[j]);
			j++;
		}
		j = 0;
		printf("\n");
		printf("MY FILES | REDIR\n");
		while (tab[i].filename[j])
		{
			printf("{%i}", tab[i].typefile[j]);
			printf("{%s}\n", tab[i].filename[j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
