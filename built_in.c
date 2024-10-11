/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:26:28 by manbengh          #+#    #+#             */
/*   Updated: 2024/10/11 20:07:32 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_strcmp_env(const char *s1, const char *s2)
// {
// 	int	i;
// 	int	j;
// 	int	len;

// 	i = 0;
// 	len = ft_strlen(s1) - 1;
// 	j = 0;
// 	while (s1[i] == ' ' || s1[i] == '\t')
// 		i++;
// 	while (s1[len] == ' ' || s1[len] == '\t')
// 		len--;
// 	while (s1[i] == s2[j] && s1[i] && s2[j])
// 		i++;
// 	printf("s1 ---> %c\n", s1[i]);
// 	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
// }

int	ft_env(t_mini *data)
{
	int	i;

	i = 0;
	if (data->env)
	{
		while (data->env->next)
		{
			printf("%s\n", data->env->content);
			data->env = data->env->next;
		}
		return (0);
	}
	return (1);
}

int	ft_built_in_comp(t_mini *data)
{
	printf("value_t --> %s\n", data->token->value_t);
	if (data->token->next)
		printf("value_t --> %s\n", data->token->next->value_t);
	if (ft_strcmp(data->token->value_t, "env") == 0)
		return (ft_env(data));
	return (0);
}
