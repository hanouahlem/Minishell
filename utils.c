/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:44:50 by manbengh          #+#    #+#             */
/*   Updated: 2024/09/24 18:50:23 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// ft_strlen_egale()
//  return i

//  find_key ()
 
//  key = substr(0, strlenegale(string))
//  return (key);

int	ft_strlen_stop(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char	*find_key_for_env(char *my_env)
{
	char	*key;

	key = ft_substr(my_env, 0, ft_strlen_stop(my_env, '='));
	return (key);
}

char	*find_value_for_env(char *my_env)
{
	char	*value;

	value = ft_substr(my_env, ft_strlen_stop(my_env, '='), ft_strlen(my_env));
	return (value);
}

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
