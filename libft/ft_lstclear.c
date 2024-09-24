/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:26:08 by ahbey             #+#    #+#             */
/*   Updated: 2023/12/08 15:31:27 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*contener;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	contener = *lst;
	while (contener != NULL)
	{
		(del)(contener->content);
		tmp = contener->next;
		free(contener);
		contener = tmp;
	}
	*lst = NULL;
}
