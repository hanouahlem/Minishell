/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:37:28 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/11 18:55:35 by ahbey            ###   ########.fr       */
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
