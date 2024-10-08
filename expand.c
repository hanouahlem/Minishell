/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:48:45 by manbengh          #+#    #+#             */
/*   Updated: 2024/10/08 16:56:48 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_value_from_key(char *str, t_mini *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->key))
		{
			printf("str = %s  value = %s\n", str, tmp->value);
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_get_key(char *str, int *i)
{
	int		j;
	char	*c;

	j = 0;
	c = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_')
		&& !ft_isdigit(str[1]))
	{
		c[j++] = str[(*i)++];
	}
	c[j] = '\0';
	return (c);
}

int	ft_expand_len(char *str, t_mini *data)
{
	int		i;
	int		n;
	char	*key;
	char	*value;

	i = 0;
	n = 0;
	while (str[i])
	{
		while (str[i] && str[i] == SQUOTE)
		{
			// printf("je suis [%c]{%i}\n", str[i], i);
			i++;
			while (str[i] && str[i] != SQUOTE)
			{
				n++;
				i++;
			}
			i++;
		}
		while (str[i] && str[i] == DQUOTE)
		{
			i++;
			while (str[i] && str[i] != DQUOTE)
			{
				while (str[i] && str[i] == '$')
				{
					i++;
					key = ft_get_key(str, &i);
					value = ft_value_from_key(key, data);
					if (value)
						n += ft_strlen(value);
				}
				if (!str[i])
					break ;
				i++;
				n++;
			}
			i++;
		}
		while (str[i] && str[i] == '$')
		{
			i++;
			key = ft_get_key(str, &i);
			value = ft_value_from_key(key, data);
			if (value)
				n += ft_strlen(value);
		}
		if (!str[i])
			break ;
		i++;
		n++;
	}
	printf("n == %d\n", n);
	return (n);
}

char	*ft_expand(char *str, t_mini *data)
{
	int		i;
	int		n;
	char	*new;
	char	*key;
	char	*value;

	i = 0;
	n = 0;
	new = ft_calloc(ft_expand_len(str, data) + 1, 1);
	while (str[i])
	{
		while (str[i] && str[i] == SQUOTE)
		{
			// printf("je suis [%c]{%i}\n", str[i], i);
			i++;
			while (str[i] && str[i] != SQUOTE)
				new[n++] = str[i++];
			i++;
		}
		if (!str[i])
			break ;
		while (str[i] && str[i] == DQUOTE)
		{
			i++;
			while (str[i] && str[i] != DQUOTE)
			{
				while (str[i] && str[i] == '$')
				{
					i++;
					key = ft_get_key(str, &i);
					value = ft_value_from_key(key, data);
					if (value)
					{
						strcat(new, value);
						n += ft_strlen(value);
					}
				}
				if (str[i] && str[i] != DQUOTE)
					new[n++] = str[i++];
			}
			i++;
		}
		if (!str[i])
			break ;
		while (str[i] && str[i] == '$')
		{
			if (!str[++i])
			{
				// printf("BACKSLASH ZERO\n");
				break ;
			}
			key = ft_get_key(str, &i);
			value = ft_value_from_key(key, data);
			if (value)
			{
				ft_strcat(new, value);
				n += ft_strlen(value);
			}
		}
		if (str[i] && str[i] != SQUOTE && str[i] != DQUOTE)
			new[n++] = str[i++];
	}
	return (new);
}
