/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:19:36 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/18 19:39:31 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_tokenisation(char *tokens)
{
	if (ft_strcmp(tokens, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(tokens, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(tokens, "<<") == 0)
		return (DBL_REDIR_IN);
	else if (ft_strcmp(tokens, ">>") == 0)
		return (DBL_REDIR_OUT);
	else if (ft_strcmp(tokens, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(tokens, " ") == 0)
		return (W_SPACE);
	else
		return (WORD);
}

t_token *add_prev(t_token *new)
{
	t_token *tmp1;
	t_token *tmp2;

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

t_token *ft_lstnew_tok(void *values)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value_t = ft_strdup(values);
	if (!new->value_t)
		return (free(new), NULL);
	new->type = ft_tokenisation(values);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token *ft_lstlast_tok(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void ft_lstadd_back_tok(t_token **lst, t_token *new)
{
	if (!lst || !new)
		return;
	if (*lst)
		ft_lstlast_tok(*lst)->next = new;
	else
		*lst = new;
}
