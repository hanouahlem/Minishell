/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:48:45 by manbengh          #+#    #+#             */
/*   Updated: 2024/10/04 20:11:48 by manbengh         ###   ########.fr       */
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
			// printf("%s = %s\n", str, tmp->value);
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*before_dollar(char *str, int *i)
{
	int		j;
	char	*res;

	j = 0;
	res = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[*i] != '$' && str[*i])
	{
		res[j] = str[*i];
		j++;
		(*i)++;
	}
	res[j] = '\0';
	return (res);
}

char	*ft_get_key(char *str, t_mini *data)
{
	int		i;
	int		j;
	char	*c;
	char	*res;

	i = 0;
	j = 0;
	res = NULL;
	c = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!c)
		return (NULL);
	if (str)
	{
		if (ft_strchr(str, '\'') != NULL)
		{
			str = delete_quote(str);
			printf("str == %s\n", str);
			return (str);
		}
		res = before_dollar(str, &i);
		if (res == NULL)
			i = 0;
		if (str[i] == '$')
		{
			i++;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_')
				&& !ft_isdigit(str[1]))
				c[j++] = str[i++];
			c[j] = '\0';
			c = ft_value_from_key(c, data);
			if (c)
				res = ft_strjoin(res, c);
		}
		// printf("str[i] === %c\n", str[i]);
		// i++;
	}
	res = ft_strjoin(res, &str[i]);
	res = delete_quote(res);
	printf("res == %s\n", res);
	free(str);
	return (res);
}

// $USER"lala"$USER

// char *res = NULL;
// while(str[i])
// {
// 	if(str[i] == '$')
// 	{
// 		res = ft_strjoin(res, ft_get_key());
// 		res = "manbenghlalamanbengh";
// 		while(str[i] = alphanum + _)
// 			i++;
// 	}
// 	else
// 	{
// 		res = ft_strcat(str[i])
// 		"manbenghlala"
// 	}
// 	i++;

// }

// $USER"$USER" ---> manbenghmanbengh
// $USER'$USER' ---> manbengh$USER

// $USER"lala"$USER
// int join_after_key()
// {
// 	char *str;
// 	char *res = NULL;
// 	int i = 0;
// 	while(str[i])
// 	{
// 		if(str[i] == '$')
// 		{
// 			res = ft_strjoin(res, ft_get_key());
// 			res = "manbenghlalamanbengh";
// 			while(str[i] = ft_isalnum)
// 				i++;
// 		}
// 		else
// 		{
// 			res = ft_strcat(str[i]);
// 			// "manbenghlala"
// 		}
// 		i++;
// 	}
// }