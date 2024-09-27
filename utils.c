/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:44:50 by manbengh          #+#    #+#             */
/*   Updated: 2024/09/25 19:22:39 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

env_t	*ft_lstnew_env(void *my_env)
{
	env_t	*new;

	new = malloc(sizeof(env_t));
	if (!new)
		return (NULL);
	new->content = ft_strdup(my_env);
	new->key = find_key_for_env(my_env);
	new->value = find_value_for_env(my_env);
	new->next = NULL;
	return (new);
}

env_t	*ft_lstlast_env(env_t *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(env_t **lst, env_t *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast_env(*lst)->next = new;
	else
		*lst = new;
}


int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char )s1[i] - (unsigned char )s2[i]);
}
