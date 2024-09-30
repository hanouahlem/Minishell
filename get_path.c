/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:26:09 by ahbey             #+#    #+#             */
/*   Updated: 2024/09/25 19:02:38 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_env(char **env)
{
	int i;
	env_t	*node;
	env_t *path;

	i = 0;
	node = NULL;
	path = NULL;
	while(env[i])
	{
		node = ft_lstnew_env(env[i]);
		if (!node)
			return ;
		// split();
		ft_lstadd_back_env(&path, node);
		i++;
	}
	// while (path)
	// {
	// 	printf("%s\n", path->content);
	// 	path = path->next;
	// }
}

// void	print_node(env_t *nodes)
// {
// 	while (nodes)
// 	{
// 		printf(("%s\n", nodes));
// 		nodes = nodes->next;
// 	}
// }

