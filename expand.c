/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:48:45 by manbengh          #+#    #+#             */
/*   Updated: 2024/10/04 16:01:54 by manbengh         ###   ########.fr       */
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
			printf("%s = %s\n", str, tmp->value);
			return (tmp->value);
			
		}	
		tmp = tmp->next;
	}
	return (NULL);
}

char    *ft_get_key(char *str, t_mini *data)
{
        int     i;
	int	j;
	char	*c;

        i = 0;
	j = 0;
	c = malloc(sizeof(char) * ft_strlen(str) + 1);
        if (str[i] == '$')
                i++;
        while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && !ft_isdigit(str[1]))
		c[j++] = str[i++];
	c[j] = '\0';
	return (ft_value_from_key(c, data));
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

