/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:28:00 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/18 19:39:31 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// printf("KEY :  %s\n", env->key);
// printf("VALUE :  %s\n\n", env->value);
void print_env(t_env *env)
{
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
}
void print_token(t_token *tokenis)
{
	int i;
	t_token *tmp;

	i = 1;
	tmp = tokenis;
	while (tmp)
	{
		// printf("type == %d\n", tmp->type);
		// if (tmp->prev != NULL)
		// 	printf("prev == %s\n\n", tmp->prev->value_t);
		printf("token [%d]== [%s]\n", tmp->type, tmp->value_t);
		tmp = tmp->next;
		i++;
	}
}

void print_parse(t_parse *tab, int size)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		if (tab[i].args)
			ft_printf("MY COMMAND {%s}\n", tab[i].args[0]);
		j = 0;
		ft_printf("MY ARG ");
		while (tab[i].args && tab[i].args[j])
		{
			ft_printf("{%s}", tab[i].args[j]);
			j++;
		}
		j = 0;
		ft_printf("\n");
		ft_printf("MY FILES | REDIR\n");
		while (tab[i].filename && tab[i].filename[j])
		{
			ft_printf("{%i}", tab[i].typefile[j]);
			ft_printf("{%s}\n", tab[i].filename[j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
