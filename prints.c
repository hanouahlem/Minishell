/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:28:00 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/16 15:51:40 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *tokenis)
{
	while (tokenis)
	{
		printf("value_t == %s\n", tokenis->value_t);
		// printf("type == %d\n", tokenis->type);
		// if (tokenis->prev != NULL)
		// 	printf("prev == %s\n\n", tokenis->prev->value_t);
		tokenis = tokenis->next;
	}
}
