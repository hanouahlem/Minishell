/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:44:02 by ahbey             #+#    #+#             */
/*   Updated: 2025/01/23 21:24:08 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quote(char *str, int *i, char c)
{
	int	flag;

	flag = 1;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == c)
		{
			flag = 0;
			break ;
		}
		(*i)++;
	}
	return (flag);
}

int	ft_quote(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!str)
		return (printf("error : null string\n"), 1);
	while (str[i])
	{
		if (str[i] == DQUOTE || str[i] == SQUOTE)
		{
			flag = ft_check_quote(str, &i, str[i]);
			if (flag == 1)
				break ;
		}
		i++;
	}
	if (flag == 1)
		return (printf(" syntax error near unexpected token\n"), 1);
	return (0);
}

int	ft_check_redir_pipe_begin(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str) - 1;
	while (str[i] == W_SPACE || str[i] == W_TAB)
		i++;
	if (str[i] == '|')
		return (1);
	while (str[len] == W_SPACE || str[len] == W_TAB)
		len--;
	if (str[len] == '>' || str[len] == '|' || str[len] == '<')
		return (1);
	return (0);
}

int	ft_check_redir(char *str, int *i)
{
	int	j;

	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (str[*i] == '|')
	{
		j = *i + 1;
		while (str[j] == ' ' || str[*i] == '\t')
			j++;
		if (str[j] == '|' || str[j] == '\0')
			return (printf(" syntax error near unexpected token \n"), 1);
	}
	if ((str[*i] == '>' && str[*i + 1] == '<') || (str[*i] == '<' && str[*i
				+ 1] == '>'))
		return (printf(" syntax error near unexpected token \n"), 1);
	if (str[*i] == '>' && str[*i + 1] == '>')
		(*i)++;
	else if (str[*i] == '<' && str[*i + 1] == '<')
		(*i)++;
	return (0);
}

int	ft_check_redir_in_out(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (ft_check_redir_pipe_begin(str) == 1)
		return (printf(" syntax error near unexpected token\n"), 1);
	while (str[i])
	{
		if (ft_check_redir(str, &i))
			return (1);
		if (str[i] == '>' || str[i] == '<')
		{
			j = i + 1;
			while (str[j] == ' ' || str[j] == '\t')
				j++;
			if (str[j] == '\0' || str[j] == '|' || str[j] == '>'
				|| str[j] == '<')
				return (printf(" syntax error near unexpected token \n"), 1);
		}
		if (str[i])
			i++;
	}
	return (0);
}  
