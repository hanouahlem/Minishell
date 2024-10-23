/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organis_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:35:32 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/22 15:47:49 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	create_cmd(t_mini *data, int i)
// {
// 	data->cmd = NULL;
// 	data->args = NULL;
// 	data->cmd[i] = ft_strdup(data->token->value_t);
	// new_cmd->num_redir_in = 0;
	// new_cmd->num_redir_out = 0;
// }
t_mini	*add_prev_org(t_mini *new)
{
	t_mini	*tmp1;
	t_mini	*tmp2;

	if (new)
	{
		new->prev = NULL;
		tmp1 = new;
		tmp2 = new->next;
		while (tmp1 && tmp2)
		{
			tmp2->prev = tmp1;
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
	}
	return (new);
}

t_mini	*ft_lstnew_org(void *values)
{
	t_mini	*new;

	new = malloc(sizeof(t_mini));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->args = NULL;
	new->index = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_mini	*ft_lstlast_org(t_mini *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_org(t_mini **lst, t_mini *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast_org(*lst)->next = new;
	else
		*lst = new;
}
