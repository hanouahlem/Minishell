/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:42:58 by manbengh          #+#    #+#             */
/*   Updated: 2024/12/31 17:04:02 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_value_from_key(char *str, t_mini *data)
{
	t_env	*tmp;

	tmp = data->env;
	if (!strcmp(str, "?"))
		return (ft_itoa(data->exit_status));
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_get_key(char *str, int *i)
{
	int		j;
	char	*c;

	j = 0;
	if (!str)
		return (NULL);
	if (str[*i] == '?')
		return ((*i)++, ft_strdup("?"));
	c = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!c)
		return (NULL);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_')
		&& !ft_isdigit(str[1]))
	{
		c[j++] = str[(*i)++];
	}
	c[j] = '\0';
	return (c);
}

void	ft_expand_len_squote(t_expand *exp_l)
{
	if (exp_l->str[exp_l->i] == SQUOTE)
	{
		exp_l->i++;
		while (exp_l->str[exp_l->i] && exp_l->str[exp_l->i] != SQUOTE)
		{
			exp_l->n++;
			exp_l->i++;
		}
		exp_l->i++;
	}
}

void	ft_expand_len_dquote(t_expand *exp_l)
{
	char	*key;
	char	*value;

	if (exp_l->str[exp_l->i] == DQUOTE)
	{
		exp_l->i++;
		while (exp_l->str[exp_l->i] && exp_l->str[exp_l->i] != DQUOTE)
		{
			if (exp_l->str[exp_l->i] == '$')
			{
				exp_l->i++;
				key = ft_get_key(exp_l->str, &(exp_l->i));
				if (!key || !*key)
					exp_l->n += 1;
				value = ft_value_from_key(key, exp_l->data);
				if (value)
					exp_l->n += ft_strlen(value);
				free(value);
				ft_free_key(key);
			}
			else
				ft_exp_plus_plus(exp_l);
		}
		exp_l->i++;
	}
}

void	ft_expand_len_dollar(t_expand *exp_l)
{
	char	*key;
	char	*value;

	if (exp_l->str[exp_l->i] == '$')
	{
		if (!exp_l->str[exp_l->i + 1])
			exp_l->n += 1;
		exp_l->i++;
		if (exp_l->str[exp_l->i] == '?')
		{
			exp_l->n += 1;
		}
		key = ft_get_key(exp_l->str, &(exp_l->i));
		value = ft_value_from_key(key, exp_l->data);
		if (value)
			exp_l->n += ft_strlen(value);
		else
			exp_l->n++;
		(free(key), free(value));
	}
}
