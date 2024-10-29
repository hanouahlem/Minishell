/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:48:45 by manbengh          #+#    #+#             */
/*   Updated: 2024/10/29 18:20:12 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expand_len(char *str, t_mini *data)
{
	t_expand	exp_l;

	exp_l.str = str;
	exp_l.i = 0;
	exp_l.n = 0;
	exp_l.data = data;
	while (exp_l.str[exp_l.i])
	{
		ft_expand_len_squote(&exp_l);
		ft_expand_len_dquote(&exp_l);
		ft_expand_len_dollar(&exp_l);
		if (exp_l.str[exp_l.i] && exp_l.str[exp_l.i] != SQUOTE
			&& exp_l.str[exp_l.i] != DQUOTE && exp_l.str[exp_l.i] != '$')
		{
			exp_l.n++;
			exp_l.i++;
		}
	}
	return (exp_l.n);
}

void	ft_expand_squote(t_expand *exp)
{
	if (exp->str[exp->i] == SQUOTE)
	{
		exp->i++;
		while (exp->str[exp->i] && exp->str[exp->i] != SQUOTE)
			exp->new_str[exp->n++] = exp->str[exp->i++];
		exp->i++;
	}
}

void	ft_expand_dquote(t_expand *exp)
{
	char	*key;
	char	*value;

	if (exp->str[exp->i] == DQUOTE)
	{
		exp->i++;
		while (exp->str[exp->i] && exp->str[exp->i] != DQUOTE)
		{
			if (exp->str[exp->i] == '$')
			{
				exp->i++;
				key = ft_get_key(exp->str, &(exp->i));
				if (!key || !*key)
					exp->new_str[exp->n++] = '$';
				value = ft_value_from_key(key, exp->data);
				if (value)
					ft_cat_value(exp, value);
			}
			else
				exp->new_str[exp->n++] = exp->str[exp->i++];
		}
		exp->i++;
	if (value)
		free(value);
	if (key)
		free(key);
	}
}

void	ft_expand_dollar(t_expand *exp)
{
	char	*key;
	char	*value;

	while (exp->str[exp->i] == '$')
	{
		exp->i++;
		key = ft_get_key(exp->str, &(exp->i));
		if (!key || !*key)
			exp->new_str[exp->n++] = '$';
		value = ft_value_from_key(key, exp->data);
		if (value)
		{
			ft_strcat(exp->new_str, value);
			exp->n += ft_strlen(value);
		}
	}
	// if (value)
	// 	free(value);
	// if (key)
	// 	free(key);
}

char	*ft_expand(char *str, t_mini *data)
{
	t_expand	exp;

	exp.str = str;
	exp.i = 0;
	exp.n = 0;
	exp.data = data;
	exp.new_str = ft_calloc(ft_expand_len(str, data) + 1, 1);
	while (exp.str[exp.i])
	{
		ft_expand_squote(&exp);
		ft_expand_dquote(&exp);
		ft_expand_dollar(&exp);
		if (exp.str[exp.i] && exp.str[exp.i] != SQUOTE
			&& exp.str[exp.i] != DQUOTE)
			exp.new_str[exp.n++] = exp.str[exp.i++];
	}
	return (exp.new_str);
}
