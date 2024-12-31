/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:48:45 by manbengh          #+#    #+#             */
/*   Updated: 2024/12/31 18:48:05 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*adding_stuff(char *str, char c);

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
			exp->new_str[exp->n++] = -exp->str[exp->i++];
		exp->i++;
	}
}

void	ft_expand_dquote(t_expand *exp)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
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
					exp->new_str[exp->n++] = -('$');
				value = ft_value_from_key(key, exp->data);
				if_value_key(exp, value, key);
			}
			else
				exp->new_str[exp->n++] = -exp->str[exp->i++];
		}
		exp->i++;
	}
}

void	ft_expand_dollar(t_expand *exp, t_mini *data)
{
	char	*key;
	char	*value;

	while (exp->str[exp->i] == '$')
	{
		exp->i++;
		if (exp->str[exp->i] == '?')
		{
			value = ft_itoa(data->exit_status);
			if (value)
				if_value(exp, value);
			continue ;
		}
		key = ft_get_key(exp->str, &(exp->i));
		if (!key || !*key)
			exp->new_str[exp->n++] = '$';
		value = ft_value_from_key(key, exp->data);
		if (value)
		{
			ft_strcat(exp->new_str, value);
			exp->n += ft_strlen(value);
		}
		(free(key), free(value));
	}
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
		ft_expand_dollar(&exp, data);
		if (exp.str[exp.i] && exp.str[exp.i] != SQUOTE
			&& exp.str[exp.i] != DQUOTE)
		{
			exp.new_str[exp.n++] = exp.str[exp.i++];
		}
	}
	return (exp.new_str);
}

// static char	*adding_stuff(char *str, char c)
// {
// 	char	*res;
// 	int			i;
// 	int			len;

// 	i = -1;
// 	len = ft_strlen(str);
// 	res = malloc(sizeof(char) * (len + 2));
// 	if (!res)
// 		return (NULL);
// 	res[i + 2] = '\0';
// 	while (str[++i])
// 		res[i] = str[i];
// 	res[i] = c;
// 	return (res);	
// }