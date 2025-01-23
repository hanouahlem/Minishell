/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:37:28 by ahbey             #+#    #+#             */
/*   Updated: 2025/01/23 21:26:15 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cat_value(t_expand *exp, char *value)
{
	ft_strcat(exp->new_str, value);
	exp->n += ft_strlen(value);
}

void	ft_exp_plus_plus(t_expand *exp_l)
{
	exp_l->n++;
	exp_l->i++;
}

void	if_value(t_expand *exp, char *value)
{
	exp->new_str = ft_strcat(exp->new_str, value);
	exp->n += ft_strlen(value);
	free(value);
}

void	ft_free_key(char *key)
{
	if (key)
		free(key);
}

void	if_value_key(t_expand *exp, char *value, char *key)
{
	if (value)
	{
		ft_cat_value(exp, value);
		free(value);
	}
	free(key);
	key = NULL;
}
