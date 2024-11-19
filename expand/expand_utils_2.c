/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:37:28 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/13 19:23:01 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cat_value(t_expand *exp, char *value)
{
	fprintf(stderr, "da da[%s]\n", exp->new_str);
	ft_strcat(exp->new_str, value);
	exp->n += ft_strlen(value);
	fprintf(stderr, "la la[%s]\n", exp->new_str);
}

void	ft_exp_plus_plus(t_expand *exp_l)
{
	exp_l->n++;
	exp_l->i++;
}
